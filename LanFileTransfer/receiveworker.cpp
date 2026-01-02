#include "receiveworker.h"
#include <QFile>
#include <QDataStream>
#include <QTcpSocket>
#include <QDebug>
#include <QDir>
#include <QByteArray>

// 定义最大安全长度（避免MaxByteArraySize断言）
const qint32 MAX_FILE_NAME_LEN = 1024;    // 文件名最长1024字节
const qint64 MAX_FILE_SIZE = 1024 * 1024 * 1024; // 文件最大1GB

ReceiveWorker::ReceiveWorker(qintptr socketDescriptor,
                             const QString &saveDir,
                             QObject *parent)
    : QThread(parent),
      m_socketDescriptor(socketDescriptor),
      m_saveDir(saveDir)
{
    // 子线程内创建Socket，避免跨线程父对象问题
    m_socket.moveToThread(this);
}

ReceiveWorker::~ReceiveWorker()
{
    if (m_socket.isOpen()) {
        m_socket.close();
    }
    quit();
    wait(1000);
}

void ReceiveWorker::run()
{
    // 1. 子线程内独立初始化Socket（核心修复：避免跨线程父对象）
    if (!m_socket.setSocketDescriptor(m_socketDescriptor)) {
        emit error("Socket初始化失败：" + m_socket.errorString());
        return;
    }
    if (!m_socket.isOpen()) {
        emit error("Socket未打开，描述符：" + QString::number(m_socketDescriptor));
        return;
    }
    qDebug() << "子线程Socket已打开，线程ID：" << QThread::currentThreadId();

    QDataStream in(&m_socket);
    in.setVersion(QDataStream::Qt_5_12); // 匹配你的Qt版本

    // ========== 步骤1：读取文件名长度（严格校验，统一类型） ==========
    qint32 nameLen = 0;
    qint64 needBytes = static_cast<qint64>(sizeof(qint32)); // 转为有符号
    if (m_socket.bytesAvailable() < needBytes) {
        if (!m_socket.waitForReadyRead(5000)) {
            emit error("读取文件名长度超时（无足够数据）");
            m_socket.close();
            return;
        }
    }
    in >> nameLen;
    // 校验长度有效性（杜绝MaxByteArraySize断言）
    if (nameLen <= 0 || nameLen > MAX_FILE_NAME_LEN) {
        emit error("无效的文件名长度：" + QString::number(nameLen) + "（合法范围：1-" +
                   QString::number(MAX_FILE_NAME_LEN) + "）");
        m_socket.close();
        return;
    }

    // ========== 步骤2：读取文件名（校验读取长度，统一类型） ==========
    QByteArray nameBytes;
    nameBytes.resize(nameLen);
    needBytes = static_cast<qint64>(nameLen); // 转为有符号
    if (m_socket.bytesAvailable() < needBytes) {
        if (!m_socket.waitForReadyRead(5000)) {
            emit error("读取文件名超时（需要" + QString::number(nameLen) + "字节，仅收到" +
                       QString::number(m_socket.bytesAvailable()) + "字节）");
            m_socket.close();
            return;
        }
    }
    qint64 readName = in.readRawData(nameBytes.data(), nameLen);
    if (readName != static_cast<qint64>(nameLen)) { // 统一为qint64比较
        emit error("文件名读取不完整：预期" + QString::number(nameLen) + "字节，实际" +
                   QString::number(readName));
        m_socket.close();
        return;
    }
    QString fileName = QString::fromUtf8(nameBytes);
    QString filePath = m_saveDir + "/" + fileName;
    // 过滤非法文件名（避免路径注入）
    if (fileName.contains("/") || fileName.contains("\\") || fileName.contains(":")) {
        emit error("文件名包含非法字符：" + fileName);
        m_socket.close();
        return;
    }

    // ========== 步骤3：读取文件大小（严格校验，统一类型） ==========
    qint64 fileSize = 0;
    needBytes = static_cast<qint64>(sizeof(qint64)); // 转为有符号
    if (m_socket.bytesAvailable() < needBytes) {
        if (!m_socket.waitForReadyRead(5000)) {
            emit error("读取文件大小超时（无足够数据）");
            m_socket.close();
            return;
        }
    }
    in >> fileSize;
    if (fileSize < 0 || fileSize > MAX_FILE_SIZE) {
        emit error("无效的文件大小：" + QString::number(fileSize) + "（合法范围：0-" +
                   QString::number(MAX_FILE_SIZE) + "）");
        m_socket.close();
        return;
    }

    // ========== 步骤4：写入文件（分段读取，避免内存溢出） ==========
    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) { // 清空已有文件
        emit error("文件打开失败：" + file.errorString() + "（路径：" + filePath + "）");
        m_socket.close();
        return;
    }

    qint64 received = 0;
    const int BUFFER_SIZE = 4096; // 小缓冲区，避免内存峰值
    while (received < fileSize) {
        // 校验剩余数据是否超过最大值
        qint64 remain = fileSize - received;
        if (remain <= 0) break;

        // 等待数据可读（超时10秒）
        if (!m_socket.waitForReadyRead(10000)) {
            emit error("文件数据接收超时：已接收" + QString::number(received) + "/" +
                       QString::number(fileSize) + "字节");
            file.close();
            QFile::remove(filePath);
            m_socket.close();
            return;
        }

        // 读取数据（最多读BUFFER_SIZE字节）
        qint64 readSize = qMin(remain, static_cast<qint64>(BUFFER_SIZE)); // 统一为qint64
        QByteArray data = m_socket.read(static_cast<int>(readSize)); // 转为int（BUFFER_SIZE是int）
        if (data.isEmpty()) {
            qDebug() << "客户端断开连接，已接收：" << received << "/" << fileSize;
            break;
        }

        // 写入文件（校验写入结果）
        qint64 writeLen = file.write(data);
        if (writeLen != static_cast<qint64>(data.size())) { // 统一为qint64比较
            emit error("文件写入失败：预期写入" + QString::number(data.size()) + "字节，实际" +
                       QString::number(writeLen) + "字节");
            file.close();
            QFile::remove(filePath);
            m_socket.close();
            return;
        }

        received += writeLen;
        // 发送进度（避免频繁触发信号，每1%更新一次）
        static int lastProgress = -1;
        int currentProgress = qRound((double)received / fileSize * 100);
        if (currentProgress != lastProgress) {
            emit progress(QString("正在接收 %1 (%2/%3, %4%)")
                          .arg(fileName)
                          .arg(received)
                          .arg(fileSize)
                          .arg(currentProgress));
            lastProgress = currentProgress;
        }
    }

    // ========== 收尾：资源清理 + 结果校验 ==========
    file.close();
    m_socket.disconnectFromHost();
    m_socket.waitForDisconnected(3000);
    m_socket.close();

    if (received == fileSize) {
        emit finished(fileName);
        qDebug() << "文件接收完成：" << fileName << "，大小：" << fileSize << "字节";
    } else {
        emit error("文件接收不完整：预期" + QString::number(fileSize) + "字节，实际" +
                   QString::number(received) + "字节");
        QFile::remove(filePath); // 删除不完整文件
    }
}

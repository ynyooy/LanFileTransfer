#include <QCoreApplication>
#include <QTcpSocket>
#include <QFile>
#include <QFileInfo>
#include <QDataStream>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // ===== 1. 配置目标地址（同机测试）=====
    QString serverIp = "127.0.0.1";
    quint16 serverPort = 45454;

    // ===== 2. 要发送的文件（请改成你本机真实存在的文件）=====
    QString filePath = "C:/Users/sano/Desktop/test.txt";   // ⚠️ 一定要存在

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "无法打开文件：" << filePath;
        return -1;
    }

    QFileInfo fileInfo(file);
    QString fileName = fileInfo.fileName();
    qint64 fileSize = file.size();

    qDebug() << "准备发送文件："
             << fileName
             << "大小：" << fileSize;

    // ===== 3. 创建 TCP Socket =====
    QTcpSocket socket;
    socket.connectToHost(serverIp, serverPort);

    if (!socket.waitForConnected(5000)) {
        qDebug() << "连接接收端失败："
                 << socket.errorString();
        return -1;
    }

    qDebug() << "连接接收端成功";

    // ===== 4. 数据流（协议一致）=====
    QDataStream out(&socket);
    out.setVersion(QDataStream::Qt_5_12);

    // ===== 5. 发送【文件名长度】=====
    QByteArray nameBytes = fileName.toUtf8();
    qint32 nameLen = nameBytes.size();

    out << nameLen;
    socket.flush();

    // ===== 6. 发送【文件名】=====
    out.writeRawData(nameBytes.data(), nameLen);
    socket.flush();

    // ===== 7. 发送【文件大小】=====
    out << fileSize;
    socket.flush();

    // ===== 8. 发送【文件内容】=====
    qint64 sent = 0;

    while (!file.atEnd()) {
        QByteArray chunk = file.read(4096);
        socket.write(chunk);
        socket.waitForBytesWritten();
        sent += chunk.size();

        qDebug() << "发送中：" << sent << "/" << fileSize;
    }

    file.close();

    qDebug() << "文件发送完成";

    socket.disconnectFromHost();

    return 0;
}

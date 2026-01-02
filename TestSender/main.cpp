#include <QCoreApplication>
#include <QTcpSocket>
#include <QDataStream>
#include <QFile>
#include <QDebug>
#include <QString>
#include <QFileInfo>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    // ==== 配置测试参数（修改为你的测试文件路径）====
    const QString targetIp = "127.0.0.1";    // 接收端IP（本机测试固定为127.0.0.1）
    const quint16 targetPort = 45454;        // 接收端端口（必须和接收端一致）
    const QString sendFilePath =
        "C:/Users/sano/Desktop/test.txt"; // 本地测试文件路径（务必修改为真实路径）

    // 1. 连接接收端
    QTcpSocket socket;
    socket.connectToHost(targetIp, targetPort);
    if (!socket.waitForConnected(3000)) { // 3秒超时
        qDebug() << "❌ 连接接收端失败：" << socket.errorString();
        return -1;
    }
    qDebug() << "✅ 连接接收端成功！";

    // 2. 打开测试文件
    QFile file(sendFilePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qDebug() << "❌ 打开文件失败：" << file.errorString();
        socket.disconnectFromHost();
        return -1;
    }
    qDebug() << "✅ 打开文件成功：" << sendFilePath;

    // 3. 按协议打包数据（严格匹配接收端）
    QDataStream out(&socket);
    out.setVersion(QDataStream::Qt_5_0); // 必须和接收端版本一致！

    // 3.1 文件名长度（qint32）
    QString fileName = QFileInfo(file).fileName();
    QByteArray nameBytes = fileName.toUtf8();
    qint32 nameLen = nameBytes.size();
    out << nameLen;
    qDebug() << "📝 发送文件名长度：" << nameLen;

    // 3.2 文件名（UTF-8）
    out.writeRawData(nameBytes.data(), nameLen);
    qDebug() << "📝 发送文件名：" << fileName;

    // 3.3 文件大小（qint64）
    qint64 fileSize = file.size();
    out << fileSize;
    qDebug() << "📝 发送文件大小：" << fileSize << "字节";

    // 3.4 文件数据
    QByteArray fileData = file.readAll();
    out.writeRawData(fileData.data(), fileSize);
    socket.flush(); // 强制刷出缓冲区（关键：避免数据滞留）
    qDebug() << "✅ 文件数据发送完成！";

    // 4. 收尾
    file.close();
    socket.disconnectFromHost();
    socket.waitForDisconnected(1000);
    qDebug() << "🔌 断开连接，发送端退出";

    return a.exec();
}

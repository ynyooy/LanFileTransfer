#include "receiveworker.h"
#include <QDataStream>
#include <QFile>
#include <QDir>
#include <QDebug>

ReceiveWorker::ReceiveWorker(qintptr socketDescriptor,
                             const QString &saveDir,
                             QObject *parent)
    : QThread(parent),
      m_socketDescriptor(socketDescriptor),
      m_saveDir(saveDir)
{
}

void ReceiveWorker::run()
{
    QTcpSocket socket;

    // ⭐ 在子线程中“重新绑定” socket
    if (!socket.setSocketDescriptor(m_socketDescriptor)) {
        emit error("绑定 socketDescriptor 失败");
        return;
    }

    emit progress("📥 新连接");

    QDataStream in(&socket);
    in.setVersion(QDataStream::Qt_5_12);

    qint32 nameLen = 0;
    if (!socket.waitForReadyRead(5000)) {
        emit error("等待文件名超时");
        return;
    }
    in >> nameLen;

    QByteArray nameData(nameLen, 0);
    in.readRawData(nameData.data(), nameLen);
    QString fileName = QString::fromUtf8(nameData);

    qint64 fileSize = 0;
    in >> fileSize;

    QDir().mkpath(m_saveDir);
    QFile file(m_saveDir + "/" + fileName);
    if (!file.open(QIODevice::WriteOnly)) {
        emit error("无法创建文件");
        return;
    }

    qint64 received = 0;
    while (received < fileSize) {
        if (!socket.waitForReadyRead(5000))
            break;

        QByteArray data = socket.readAll();
        file.write(data);
        received += data.size();

        emit progress(QString("接收中 %1 / %2")
                      .arg(received)
                      .arg(fileSize));
    }

    file.close();
    socket.disconnectFromHost();

    emit finished(fileName);
}



#include "receiveworker.h"
#include <QFile>
#include <QDataStream>

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
    socket.setSocketDescriptor(m_socketDescriptor);

    QDataStream in(&socket);
    in.setVersion(QDataStream::Qt_5_0);

    // 文件名长度
    qint32 nameLen;
    socket.waitForReadyRead();
    in >> nameLen;

    // 文件名
    QByteArray nameBytes;
    nameBytes.resize(nameLen);
    in.readRawData(nameBytes.data(), nameLen);
    QString fileName = QString::fromUtf8(nameBytes);

    // 文件大小
    qint64 fileSize;
    in >> fileSize;

    QFile file(m_saveDir + "/" + fileName);
    file.open(QIODevice::WriteOnly);

    qint64 received = 0;
    while (received < fileSize) {
        if (!socket.waitForReadyRead())
            break;

        QByteArray data = socket.readAll();
        file.write(data);
        received += data.size();

        emit progress(QString("正在接收 %1 (%2/%3)")
                      .arg(fileName)
                      .arg(received)
                      .arg(fileSize));
    }

    file.close();
    socket.disconnectFromHost();

    emit finished(fileName);
}


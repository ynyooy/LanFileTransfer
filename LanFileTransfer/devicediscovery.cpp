#include "devicediscovery.h"
#include <QHostAddress>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkInterface>

static const quint16 DISCOVERY_PORT = 45455;

DeviceDiscovery::DeviceDiscovery(QObject *parent)
    : QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    udpSocket->bind(QHostAddress::AnyIPv4,
                    DISCOVERY_PORT,
                    QUdpSocket::ShareAddress | QUdpSocket::ReuseAddressHint);

    connect(udpSocket, &QUdpSocket::readyRead,
            this, &DeviceDiscovery::readPendingDatagrams);

    broadcastTimer = new QTimer(this);
    broadcastTimer->setInterval(2000); // 每 2 秒广播一次
    connect(broadcastTimer, &QTimer::timeout,
            this, &DeviceDiscovery::sendBroadcast);
}

void DeviceDiscovery::start()
{
    broadcastTimer->start();
}

void DeviceDiscovery::stop()
{
    broadcastTimer->stop();
}

void DeviceDiscovery::sendBroadcast()
{
    QJsonObject obj;
    obj["name"] = "LocalSend-PC";
    obj["port"] = 45454;

    QJsonDocument doc(obj);
    QByteArray data = doc.toJson(QJsonDocument::Compact);

    udpSocket->writeDatagram(
        data,
        QHostAddress::Broadcast,
        DISCOVERY_PORT
    );
}

void DeviceDiscovery::readPendingDatagrams()
{
    while (udpSocket->hasPendingDatagrams()) {

        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());

        QHostAddress sender;
        quint16 senderPort;

        udpSocket->readDatagram(
            datagram.data(),
            datagram.size(),
            &sender,
            &senderPort
        );

        QJsonDocument doc = QJsonDocument::fromJson(datagram);
        if (!doc.isObject())
            continue;

        QJsonObject obj = doc.object();

        DeviceInfo device;
        device.name = obj["name"].toString();
        device.ip = sender.toString();
        device.port = obj["port"].toInt();

        emit deviceFound(device);
    }
}

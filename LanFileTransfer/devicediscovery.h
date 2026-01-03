#ifndef DEVICEDISCOVERY_H
#define DEVICEDISCOVERY_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>

struct DeviceInfo {
    QString name;
    QString ip;
    quint16 port;
};

class DeviceDiscovery : public QObject
{
    Q_OBJECT
public:
    explicit DeviceDiscovery(QObject *parent = nullptr);

    void start();
    void stop();

signals:
    void deviceFound(const DeviceInfo &device);

private slots:
    void sendBroadcast();
    void readPendingDatagrams();

private:
    QUdpSocket *udpSocket;
    QTimer *broadcastTimer;
};

#endif

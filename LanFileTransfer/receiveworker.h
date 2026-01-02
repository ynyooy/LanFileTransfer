// receiveworker.h
#ifndef RECEIVEWORKER_H
#define RECEIVEWORKER_H

#include <QThread>
#include <QTcpSocket>

class ReceiveWorker : public QThread
{
    Q_OBJECT
public:
    explicit ReceiveWorker(qintptr socketDescriptor,
                           const QString &saveDir,
                           QObject *parent = nullptr);
    ~ReceiveWorker() override;

protected:
    void run() override;

signals:
    void progress(QString info);
    void finished(QString name);
    void error(QString err);

private:
    qintptr m_socketDescriptor;
    QString m_saveDir;
    QTcpSocket m_socket; // 子线程内的Socket，无跨线程父对象
};

#endif // RECEIVEWORKER_H

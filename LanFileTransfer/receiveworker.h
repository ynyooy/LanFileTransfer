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

signals:
    void progress(QString info);
    void finished(QString fileName);

protected:
    void run() override;

private:
    qintptr m_socketDescriptor;
    QString m_saveDir;
};

#endif // RECEIVEWORKER_H

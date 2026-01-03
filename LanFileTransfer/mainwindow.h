#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include <QStandardItemModel>
#include <QTimer>
#include "devicediscovery.h"
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sendButton_clicked();
    void on_receiveButton_clicked();
    void on_settingsButton_clicked();
    void onNewConnection();
    void on_btnStartReceive_clicked();
    void on_btnStopReceive_clicked();
    void on_btnChooseSavePath_clicked();
    void onDeviceSelected(const QModelIndex &index);
    void on_btnSendFile_clicked();

    void on_btnSendFolder_clicked();

    void on_btnSendText_clicked();

    void on_btnrefresh_clicked();

private:
    Ui::MainWindow *ui;
    QTcpServer *tcpServer;
    QStandardItemModel *receiveModel;
    DeviceDiscovery *deviceDiscovery;


    QStandardItemModel *deviceModel;
    QString m_targetIp;
    quint16 m_targetPort;
    void sendFile(const QString &filePath);
    void sendText(const QString &text);
};

#endif // MAINWINDOW_H


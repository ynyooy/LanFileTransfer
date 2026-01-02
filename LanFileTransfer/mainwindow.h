#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
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

private:
    Ui::MainWindow *ui;
    QTcpServer *tcpServer;
    QStandardItemModel *receiveModel;
};

#endif // MAINWINDOW_H


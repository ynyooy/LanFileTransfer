#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "receiveworker.h"
#include <QTcpServer>
#include <QTcpSocket>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 默认显示“发送页面”
    ui->stackedWidget->setCurrentWidget(ui->pageSend);
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection,
            this, &MainWindow::onNewConnection);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 点击“发送”
void MainWindow::on_sendButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSend);
}

// 点击“接收”
void MainWindow::on_receiveButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageReceive);
}

// 点击“设置”
void MainWindow::on_settingsButton_clicked()
{
    ui->stackedWidget->setCurrentWidget(ui->pageSettings);
}


void MainWindow::on_btnStartReceive_clicked()
{
    if (ui->editSavePath->text().isEmpty()) {
        ui->lblReceiveStatus->setText("状态：请选择保存路径");
        return;
    }

    if (!tcpServer->listen(QHostAddress::Any, 45454)) {
        ui->lblReceiveStatus->setText("监听失败");
        return;
    }

    ui->lblReceiveStatus->setText("状态：正在监听端口 45454");
    ui->btnStartReceive->setEnabled(false);
    ui->btnStopReceive->setEnabled(true);
}



void MainWindow::on_btnStopReceive_clicked()
{
    tcpServer->close();

    ui->lblReceiveStatus->setText("状态：已停止监听");
    ui->btnStartReceive->setEnabled(true);
    ui->btnStopReceive->setEnabled(false);
}


void MainWindow::onNewConnection()
{
    QTcpSocket *client = tcpServer->nextPendingConnection();
    qintptr sd = client->socketDescriptor();
    client->deleteLater();

    ReceiveWorker *worker =
        new ReceiveWorker(sd, ui->editSavePath->text());

    connect(worker, &ReceiveWorker::progress, this, [ = ](QString info) {
        receiveModel->appendRow(new QStandardItem(info));
    });

    connect(worker, &ReceiveWorker::finished, this, [ = ](QString name) {
        receiveModel->appendRow(
            new QStandardItem("接收完成：" + name));
        worker->deleteLater();
    });

    worker->start();
}



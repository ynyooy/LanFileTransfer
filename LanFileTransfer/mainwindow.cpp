#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "receiveworker.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QDir>
#include <QStandardItemModel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , tcpServer(nullptr)
    , receiveModel(nullptr) //初始化模型
{
    ui->setupUi(this);

    // 默认显示“发送页面”
    ui->stackedWidget->setCurrentWidget(ui->pageSend);

    //初始化接受任务模型
    receiveModel = new QStandardItemModel(this);
    //  初始化TCP服务器并启动监听
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection,
            this, &MainWindow::onNewConnection);

    //初始化按钮状态
    ui->btnStartReceive->setEnabled(true);
    ui->btnStopReceive->setEnabled(false);
}

MainWindow::~MainWindow()
{
    // 安全释放资源
    if (tcpServer) {
        tcpServer->close();
    }
    delete receiveModel; // 释放模型
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
    QDir saveDir(ui->editSavePath->text());
    if (!saveDir.exists()) {
        if (!saveDir.mkpath(".")) {
            ui->lblReceiveStatus->setText("状态：创建保存路径失败");
            return;
        }
    }
    if (!tcpServer->listen(QHostAddress::AnyIPv4, 45454)) {
        ui->lblReceiveStatus->setText("状态：监听失败（端口被占用/权限不足）");
        qDebug() << "监听失败原因：" << tcpServer->errorString();
        return;
    }

    ui->lblReceiveStatus->setText("状态：正在监听端口 45454");
    ui->btnStartReceive->setEnabled(false);
    ui->btnStopReceive->setEnabled(true);
}



void MainWindow::on_btnStopReceive_clicked()
{
    if (tcpServer->isListening()) {
        tcpServer->close();
    }

    ui->lblReceiveStatus->setText("状态：已停止监听");
    ui->btnStartReceive->setEnabled(true);
    ui->btnStopReceive->setEnabled(false);
}


// mainwindow.cpp 中 onNewConnection 函数
void MainWindow::onNewConnection()
{
    while (tcpServer->hasPendingConnections()) {
        QTcpSocket *client = tcpServer->nextPendingConnection();
        if (!client) {
            qDebug() << "新连接为空";
            continue;
        }

        // 关键：先断开Socket的父子关系，避免跨线程父对象问题
        client->setParent(nullptr);

        // 校验Socket状态
        if (!client->isOpen()) {
            qDebug() << "Socket未打开，关闭连接";
            client->deleteLater();
            continue;
        }

        qintptr sd = client->socketDescriptor();
        QString savePath = ui->editSavePath->text();
        qDebug() << "新客户端连接：" << client->peerAddress().toString() << "，描述符：" << sd;

        // ========== 核心修复：立即释放主线程Socket，避免跨线程冲突 ==========
        client->close(); // 先关闭主线程Socket
        client->deleteLater();

        // 创建接收线程（仅传递描述符，不依赖主线程Socket对象）
        ReceiveWorker *worker = new ReceiveWorker(sd, savePath);

        // 线程安全连接信号（必须用QueuedConnection）
        connect(worker, &ReceiveWorker::progress, this, [ = ](QString info) {
            if (receiveModel) {
                receiveModel->appendRow(new QStandardItem(info));
            }
        }, Qt::QueuedConnection);

        connect(worker, &ReceiveWorker::finished, this, [ = ](QString name) {
            if (receiveModel) {
                receiveModel->appendRow(new QStandardItem("✅ 接收完成：" + name));
            }
            worker->deleteLater();
        }, Qt::QueuedConnection);

        connect(worker, &ReceiveWorker::error, this, [ = ](QString err) {
            if (receiveModel) {
                receiveModel->appendRow(new QStandardItem("❌ 错误：" + err));
            }
            worker->deleteLater();
        }, Qt::QueuedConnection);

        // 启动线程
        worker->start();
    }
}



#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "receiveworker.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
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
    ui->receiveListView->setModel(receiveModel);
    //  初始化TCP服务器并启动监听
    tcpServer = new QTcpServer(this);
    connect(tcpServer, &QTcpServer::newConnection,
            this, &MainWindow::onNewConnection);

    //初始化按钮状态
    ui->btnStartReceive->setEnabled(true);
    ui->btnStopReceive->setEnabled(false);

    //==============================设备识别============================
    deviceModel = new QStandardItemModel(this);
    ui->fileListView->setModel(deviceModel);

    deviceDiscovery = new DeviceDiscovery(this);

    connect(deviceDiscovery, &DeviceDiscovery::deviceFound,
    this, [ = ](const DeviceInfo & device) {

        QString text = QString("%1 (%2)")
                       .arg(device.name)
                       .arg(device.ip);

        // 防重复
        for (int i = 0; i < deviceModel->rowCount(); ++i) {
            if (deviceModel->item(i)->text() == text)
                return;
        }

        QStandardItem *item = new QStandardItem(text);
        item->setData(device.ip, Qt::UserRole);
        item->setData(device.port, Qt::UserRole + 1);

        deviceModel->appendRow(item);
    });

    deviceDiscovery->start();
    //------------------------------------------------------------------

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



void MainWindow::onNewConnection()
{
    while (tcpServer->hasPendingConnections()) {

        QTcpSocket *client = tcpServer->nextPendingConnection();
        if (!client)
            return;

        qDebug() << "新连接：" << client->peerAddress().toString();

        // ⭐ 1. 取 socketDescriptor（此时是有效的）
        qintptr socketDescriptor = client->socketDescriptor();

        // ⭐ 2. 不 close，不 delete
        client->setParent(nullptr);

        // ⭐ 3. 保存路径
        QString savePath = ui->editSavePath->text();

        // ⭐ 4. 创建接收线程
        ReceiveWorker *worker =
            new ReceiveWorker(socketDescriptor, savePath);

        connect(worker, &ReceiveWorker::progress, this,
        [ = ](const QString & msg) {
            receiveModel->appendRow(new QStandardItem(msg));
        });

        connect(worker, &ReceiveWorker::finished, this,
        [ = ](const QString & fileName) {
            receiveModel->appendRow(
                new QStandardItem("✅ 接收完成：" + fileName));
        });

        connect(worker, &ReceiveWorker::error, this,
        [ = ](const QString & msg) {
            receiveModel->appendRow(
                new QStandardItem("❌ 错误：" + msg));
        });

        connect(worker, &QThread::finished,
                worker, &QObject::deleteLater);

        worker->start();
    }
}




void MainWindow::on_btnChooseSavePath_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(
                      this,
                      "选择接收文件保存路径",
                      QDir::homePath()
                  );

    if (!dir.isEmpty()) {
        ui->editSavePath->setText(dir);
        ui->lblReceiveStatus->setText("状态：保存路径已设置");
    }
}






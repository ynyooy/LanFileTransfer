#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "receiveworker.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QMessageBox>
#include <QInputDialog>



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

    //实现文件发送
    connect(ui->fileListView, &QListView::clicked,
            this, &MainWindow::onDeviceSelected);

    connect(ui->btnSendFile, &QPushButton::clicked,
            this, &MainWindow::on_btnSendFile_clicked);


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


//==================================实现文件发送=================================
void MainWindow::onDeviceSelected(const QModelIndex &index)
{
    QStandardItem *item = deviceModel->itemFromIndex(index);
    if (!item) return;

    m_targetIp = item->data(Qt::UserRole).toString();
    m_targetPort = item->data(Qt::UserRole + 1).toUInt();

    qDebug() << "选择设备：" << m_targetIp << m_targetPort;
}

void MainWindow::sendFile(const QString &filePath)
{
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "错误", "无法打开文件");
        return;
    }

    QFileInfo info(filePath);
    QString fileName = info.fileName();
    qint64 fileSize = file.size();

    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 45454);

    if (!socket.waitForConnected(5000)) {
        QMessageBox::critical(this, "错误", "连接接收端失败");
        return;
    }

    QDataStream out(&socket);
    out.setVersion(QDataStream::Qt_5_12);

    // ===== 协议开始 =====

    QByteArray nameBytes = fileName.toUtf8();
    qint32 nameLen = nameBytes.size();

    out << nameLen;
    out.writeRawData(nameBytes.data(), nameLen);
    out << fileSize;

    socket.flush();
    socket.disconnectFromHost();

    // ===== 发送文件内容 =====

    qint64 sent = 0;
    while (!file.atEnd()) {
        QByteArray chunk = file.read(4096);
        socket.write(chunk);
        socket.waitForBytesWritten(3000);
        sent += chunk.size();
    }

    file.close();
    socket.disconnectFromHost();

    QMessageBox::information(this, "完成",
                             QString("文件发送完成：%1").arg(fileName));
}

void MainWindow::on_btnSendFile_clicked()
{
    if (m_targetIp.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择接收设备");
        return;
    }

    QString filePath = QFileDialog::getOpenFileName(
                           this,
                           "选择要发送的文件",
                           QDir::homePath()
                       );

    if (filePath.isEmpty())
        return;

    sendFile(filePath);
}

void MainWindow::sendText(const QString &text)
{
    QTcpSocket socket;
    socket.connectToHost(m_targetIp, m_targetPort);

    if (!socket.waitForConnected(5000)) {
        QMessageBox::critical(this, "错误", "连接接收端失败");
        return;
    }

    QDataStream out(&socket);
    out.setVersion(QDataStream::Qt_5_12);

    qint8 type = 3; // TEXT
    QByteArray textBytes = text.toUtf8();
    qint32 textLen = textBytes.size();

    out << type;
    out << textLen;
    out.writeRawData(textBytes.data(), textLen);

    socket.flush();
    socket.waitForBytesWritten(3000);
    socket.disconnectFromHost();

    QMessageBox::information(this, "完成", "文本发送完成");
}

void MainWindow::collectFiles(const QString &baseDir,
                              const QString &currentDir,
                              QList<QPair<QString, QString>> &files)
{
    QDir dir(currentDir);
    QFileInfoList list = dir.entryInfoList(
                             QDir::Files | QDir::Dirs | QDir::NoDotAndDotDot
                         );

    for (const QFileInfo &info : list) {
        if (info.isDir()) {
            collectFiles(baseDir, info.absoluteFilePath(), files);
        } else {
            QString relativePath =
                QDir(baseDir).relativeFilePath(info.absoluteFilePath());
            files.append({info.absoluteFilePath(), relativePath});
        }
    }
}
void MainWindow::sendFolder(const QString &folderPath)
{
    QList<QPair<QString, QString>> files;
    collectFiles(folderPath, folderPath, files);

    if (files.isEmpty()) {
        QMessageBox::warning(this, "提示", "文件夹为空");
        return;
    }

    QTcpSocket socket;
    socket.connectToHost(m_targetIp, m_targetPort);

    if (!socket.waitForConnected(5000)) {
        QMessageBox::critical(this, "错误", "连接接收端失败");
        return;
    }

    QDataStream out(&socket);
    out.setVersion(QDataStream::Qt_5_12);

    qint8 type = 2; // FOLDER
    out << type;

    out << static_cast<qint32>(files.size());

    for (auto &pair : files) {
        QFile file(pair.first);
        if (!file.open(QIODevice::ReadOnly))
            continue;

        QByteArray pathBytes = pair.second.toUtf8();
        qint32 pathLen = pathBytes.size();
        qint64 fileSize = file.size();

        out << pathLen;
        out.writeRawData(pathBytes.data(), pathLen);
        out << fileSize;

        while (!file.atEnd()) {
            QByteArray chunk = file.read(4096);
            socket.write(chunk);
            socket.waitForBytesWritten();
        }

        file.close();
    }

    socket.disconnectFromHost();

    QMessageBox::information(this, "完成", "文件夹发送完成");
}

void MainWindow::on_btnSendFolder_clicked()
{
    if (m_targetIp.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择接收设备");
        return;
    }

    QString dir = QFileDialog::getExistingDirectory(
                      this,
                      "选择要发送的文件夹",
                      QDir::homePath()
                  );

    if (dir.isEmpty())
        return;

    sendFolder(dir);
}


void MainWindow::on_btnSendText_clicked()
{
    if (m_targetIp.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择接收设备");
        return;
    }

    bool ok = false;
    QString text = QInputDialog::getMultiLineText(
                       this,
                       "发送文本",
                       "请输入要发送的文本：",
                       "",
                       &ok
                   );

    if (!ok || text.isEmpty())
        return;

    sendText(text);
}


void MainWindow::on_btnrefresh_clicked()
{
    deviceModel->clear();

    QStandardItem *item = new QStandardItem("本机 (127.0.0.1)");
    item->setData("127.0.0.1", Qt::UserRole);
    item->setData(45454, Qt::UserRole + 1);

    deviceModel->appendRow(item);
}



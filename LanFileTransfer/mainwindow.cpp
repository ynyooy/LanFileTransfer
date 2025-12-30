#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QListView>
#include <QProgressBar>
#include <QPushButton>
#include <QLabel>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 连接信号与槽
    connect(ui->receiveButton, &QPushButton::clicked, this, &MainWindow::onReceiveClicked);
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::onSendClicked);
    connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::onSettingsClicked);

    connect(ui->selectFileButton, &QPushButton::clicked, this, &MainWindow::onSelectFileClicked);
    connect(ui->selectFolderButton, &QPushButton::clicked, this, &MainWindow::onSelectFolderClicked);
    connect(ui->selectTextButton, &QPushButton::clicked, this, &MainWindow::onSelectTextClicked);

    // 模拟设备列表
    QStringList devices = {"设备1", "设备2", "设备3"};
    ui->deviceListView->addItems(devices);

    // 设置进度条
    ui->transferProgressBar->setRange(0, 100);
    ui->transferProgressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 接收按钮点击事件
void MainWindow::onReceiveClicked()
{
    // 接收文件的逻辑
}

// 发送按钮点击事件
void MainWindow::onSendClicked()
{
    // 发送文件的逻辑
}

// 设置按钮点击事件
void MainWindow::onSettingsClicked()
{
    // 设置逻辑
}

// 选择文件按钮点击事件
void MainWindow::onSelectFileClicked()
{
    QString file = QFileDialog::getOpenFileName(this, "选择文件", "", "All Files (*)");
    if (!file.isEmpty()) {
        ui->fileListView->addItem(file);  // 添加文件到文件列表
    }
}

// 选择文件夹按钮点击事件
void MainWindow::onSelectFolderClicked()
{
    QString folder = QFileDialog::getExistingDirectory(this, "选择文件夹");
    if (!folder.isEmpty()) {
        ui->folderListView->addItem(folder);  // 添加文件夹到文件夹列表
    }
}

// 选择文本按钮点击事件
void MainWindow::onSelectTextClicked()
{
    QString text = QFileDialog::getOpenFileName(this, "选择文本文件", "", "Text Files (*.txt)");
    if (!text.isEmpty()) {
        ui->textListView->addItem(text);  // 添加文本文件到文本列表
    }
}

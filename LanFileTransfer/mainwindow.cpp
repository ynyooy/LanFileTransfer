#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QListView>
#include <QTimer>  // 用于模拟传输延迟

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    taskModel(nullptr)  // 初始化模型指针
{
    ui->setupUi(this);

    // 初始化任务列表
    initializeTaskList();

    //信号槽连接
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::on_sendButton_clicked);
    connect(ui->receiveButton, &QPushButton::clicked, this, &MainWindow::on_receiveButton_clicked);
    connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::on_settingsButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete taskModel;
}

void MainWindow::initializeTaskList()
{
    // 创建任务模型，设置列数和表头
    taskModel = new QStandardItemModel(this);
    taskModel->setHorizontalHeaderLabels(QStringList() << "传输任务");

    // 设置模型到QListView
    ui->fileListView->setModel(taskModel);

    // 添加任务示例
    QStandardItem *taskItem = new QStandardItem("待传输任务");
    taskModel->appendRow(taskItem);
}

void MainWindow::on_sendButton_clicked()
{
    // 打开文件选择对话框
    QString filePath = QFileDialog::getOpenFileName(this, "选择要发送的文件",  QDir::homePath(),
                                                    "所有文件 (*.*);;文档 (*.docx;*.txt);;图片 (*.jpg;*.png)");
    if (!filePath.isEmpty()) {
        QStandardItem *taskItem = new QStandardItem("正在发送: " + QFileInfo(filePath).fileName());
        taskModel->appendRow(taskItem);

        // 模拟文件传输
        QTimer::singleShot(2000, this, [ = ]() { // 2秒后标记完成
            taskItem->setText("发送完成: " + QFileInfo(filePath).fileName());
        });
    }
}

void MainWindow::on_settingsButton_clicked()
{
    // 设置界面的逻辑
    QMessageBox::information(this, "设置", "设置功能尚未实现");
}

void MainWindow::on_receiveButton_clicked()
{
    // 实现接收文件逻辑
    QString receivePath = QFileDialog::getExistingDirectory(this, "选择接收文件夹",
                                                            QDir::homePath());
    if (!receivePath.isEmpty()) {
        QStandardItem *taskItem = new QStandardItem("正在接收: 目标路径 - " + receivePath);
        taskModel->appendRow(taskItem);

        // 模拟接收延迟
        QTimer::singleShot(1500, this, [ = ]() { // 1.5秒后标记完成
            taskItem->setText("接收完成: 已保存至 - " + receivePath);
        });
    }
}

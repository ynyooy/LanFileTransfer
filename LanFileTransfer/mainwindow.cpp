#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QFileDialog>
#include <QMessageBox>
#include <QListView>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //调用函数初始化任务列表
    initializeTaskList();

    //连接信号与槽
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::on_sendButton_clicked);
    connect(ui->receiveButton, &QPushButton::clicked, this, &MainWindow::on_settingsButton_clicked);
    connect(ui->settingsButton, &QPushButton::clicked, this, &MainWindow::on_receiveButton_clicked);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeTaskList()
{
    //创建任务模型
    taskModel = new QStandardItemModel;

    //设置模型到QListView
    ui->fileListView->setModel(taskModel);

    // 添加任务示例
    QStandardItem *taskItem = new QStandardItem("传输文件1");
    taskModel->appendRow(taskItem);
}




void MainWindow::on_sendButton_clicked()
{

}


void MainWindow::on_settingsButton_clicked()
{

}


void MainWindow::on_receiveButton_clicked()
{

}


#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStandardItemModel>
#include<QStandardItem>
#include<QListView>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_sendButton_clicked();

    void on_settingsButton_clicked();

    void on_receiveButton_clicked();

private:
    Ui::MainWindow *ui;

    // 添加 QStandardItemModel 成员变量
    QStandardItemModel *taskModel;  // 用于管理任务列表模型

    // 在构造函数中初始化和更新任务列表模型
    void initializeTaskList();
};
#endif // MAINWINDOW_H

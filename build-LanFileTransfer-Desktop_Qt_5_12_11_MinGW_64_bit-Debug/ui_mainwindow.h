/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.11
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *lblTitle;
    QPushButton *sendButton;
    QPushButton *settingsButton;
    QPushButton *receiveButton;
    QSpacerItem *verticalSpacer;
    QStackedWidget *stackedWidget;
    QWidget *pageSend;
    QVBoxLayout *verticalLayout_4;
    QLabel *lblSubtitle;
    QFrame *line;
    QVBoxLayout *vboxLayout;
    QLabel *lblSelection;
    QHBoxLayout *hboxLayout;
    QPushButton *btnSendFile;
    QPushButton *btnSendFolder;
    QPushButton *btnSendText;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout1;
    QLabel *lblDevicesTitle;
    QPushButton *btnrefresh;
    QListView *fileListView;
    QWidget *pageReceive;
    QVBoxLayout *vboxLayout2;
    QLabel *lblReceiveTitle;
    QHBoxLayout *hboxLayout2;
    QLabel *label;
    QLineEdit *editSavePath;
    QPushButton *btnChooseSavePath;
    QLabel *lblReceiveStatus;
    QListView *receiveListView;
    QHBoxLayout *hboxLayout3;
    QPushButton *btnStartReceive;
    QPushButton *btnStopReceive;
    QWidget *pageSettings;
    QVBoxLayout *vboxLayout3;
    QLabel *label1;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(507, 277);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_4 = new QHBoxLayout(centralwidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        lblTitle = new QLabel(centralwidget);
        lblTitle->setObjectName(QString::fromUtf8("lblTitle"));

        verticalLayout->addWidget(lblTitle);

        sendButton = new QPushButton(centralwidget);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));

        verticalLayout->addWidget(sendButton);

        settingsButton = new QPushButton(centralwidget);
        settingsButton->setObjectName(QString::fromUtf8("settingsButton"));

        verticalLayout->addWidget(settingsButton);

        receiveButton = new QPushButton(centralwidget);
        receiveButton->setObjectName(QString::fromUtf8("receiveButton"));

        verticalLayout->addWidget(receiveButton);

        verticalSpacer = new QSpacerItem(0, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_4->addLayout(verticalLayout);

        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        pageSend = new QWidget();
        pageSend->setObjectName(QString::fromUtf8("pageSend"));
        verticalLayout_4 = new QVBoxLayout(pageSend);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        lblSubtitle = new QLabel(pageSend);
        lblSubtitle->setObjectName(QString::fromUtf8("lblSubtitle"));

        verticalLayout_4->addWidget(lblSubtitle);

        line = new QFrame(pageSend);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);

        verticalLayout_4->addWidget(line);

        vboxLayout = new QVBoxLayout();
        vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
        lblSelection = new QLabel(pageSend);
        lblSelection->setObjectName(QString::fromUtf8("lblSelection"));

        vboxLayout->addWidget(lblSelection);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        btnSendFile = new QPushButton(pageSend);
        btnSendFile->setObjectName(QString::fromUtf8("btnSendFile"));

        hboxLayout->addWidget(btnSendFile);

        btnSendFolder = new QPushButton(pageSend);
        btnSendFolder->setObjectName(QString::fromUtf8("btnSendFolder"));

        hboxLayout->addWidget(btnSendFolder);

        btnSendText = new QPushButton(pageSend);
        btnSendText->setObjectName(QString::fromUtf8("btnSendText"));

        hboxLayout->addWidget(btnSendText);


        vboxLayout->addLayout(hboxLayout);


        verticalLayout_4->addLayout(vboxLayout);

        vboxLayout1 = new QVBoxLayout();
        vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
        hboxLayout1 = new QHBoxLayout();
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        lblDevicesTitle = new QLabel(pageSend);
        lblDevicesTitle->setObjectName(QString::fromUtf8("lblDevicesTitle"));

        hboxLayout1->addWidget(lblDevicesTitle);

        btnrefresh = new QPushButton(pageSend);
        btnrefresh->setObjectName(QString::fromUtf8("btnrefresh"));

        hboxLayout1->addWidget(btnrefresh);


        vboxLayout1->addLayout(hboxLayout1);

        fileListView = new QListView(pageSend);
        fileListView->setObjectName(QString::fromUtf8("fileListView"));

        vboxLayout1->addWidget(fileListView);


        verticalLayout_4->addLayout(vboxLayout1);

        stackedWidget->addWidget(pageSend);
        pageReceive = new QWidget();
        pageReceive->setObjectName(QString::fromUtf8("pageReceive"));
        vboxLayout2 = new QVBoxLayout(pageReceive);
        vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
        lblReceiveTitle = new QLabel(pageReceive);
        lblReceiveTitle->setObjectName(QString::fromUtf8("lblReceiveTitle"));

        vboxLayout2->addWidget(lblReceiveTitle);

        hboxLayout2 = new QHBoxLayout();
        hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
        label = new QLabel(pageReceive);
        label->setObjectName(QString::fromUtf8("label"));

        hboxLayout2->addWidget(label);

        editSavePath = new QLineEdit(pageReceive);
        editSavePath->setObjectName(QString::fromUtf8("editSavePath"));

        hboxLayout2->addWidget(editSavePath);

        btnChooseSavePath = new QPushButton(pageReceive);
        btnChooseSavePath->setObjectName(QString::fromUtf8("btnChooseSavePath"));

        hboxLayout2->addWidget(btnChooseSavePath);


        vboxLayout2->addLayout(hboxLayout2);

        lblReceiveStatus = new QLabel(pageReceive);
        lblReceiveStatus->setObjectName(QString::fromUtf8("lblReceiveStatus"));

        vboxLayout2->addWidget(lblReceiveStatus);

        receiveListView = new QListView(pageReceive);
        receiveListView->setObjectName(QString::fromUtf8("receiveListView"));

        vboxLayout2->addWidget(receiveListView);

        hboxLayout3 = new QHBoxLayout();
        hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
        btnStartReceive = new QPushButton(pageReceive);
        btnStartReceive->setObjectName(QString::fromUtf8("btnStartReceive"));

        hboxLayout3->addWidget(btnStartReceive);

        btnStopReceive = new QPushButton(pageReceive);
        btnStopReceive->setObjectName(QString::fromUtf8("btnStopReceive"));

        hboxLayout3->addWidget(btnStopReceive);


        vboxLayout2->addLayout(hboxLayout3);

        stackedWidget->addWidget(pageReceive);
        pageSettings = new QWidget();
        pageSettings->setObjectName(QString::fromUtf8("pageSettings"));
        vboxLayout3 = new QVBoxLayout(pageSettings);
        vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
        label1 = new QLabel(pageSettings);
        label1->setObjectName(QString::fromUtf8("label1"));

        vboxLayout3->addWidget(label1);

        stackedWidget->addWidget(pageSettings);

        horizontalLayout_4->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "LocalSend", nullptr));
        lblTitle->setText(QApplication::translate("MainWindow", "<html><p align=\"center\">\n"
"<span style=\"font-size:15pt; font-weight:300; color:#2196f3;\">LocalSend</span>\n"
"</p></html>", nullptr));
        sendButton->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        settingsButton->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        receiveButton->setText(QApplication::translate("MainWindow", "\346\216\245\346\224\266", nullptr));
        lblSubtitle->setText(QApplication::translate("MainWindow", "<html><p align=\"center\">\n"
"<span style=\"font-size:12pt; color:#555;\">\350\267\250\345\271\263\345\217\260\345\261\200\345\237\237\347\275\221\346\226\207\344\273\266\344\274\240\350\276\223</span>\n"
"</p></html>", nullptr));
        lblSelection->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251\345\217\221\351\200\201\345\206\205\345\256\271", nullptr));
        btnSendFile->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        btnSendFolder->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\345\244\271", nullptr));
        btnSendText->setText(QApplication::translate("MainWindow", "\346\226\207\346\234\254", nullptr));
        lblDevicesTitle->setText(QApplication::translate("MainWindow", "\351\231\204\350\277\221\347\232\204\350\256\276\345\244\207", nullptr));
        btnrefresh->setText(QApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
        lblReceiveTitle->setText(QApplication::translate("MainWindow", "<h3>\346\216\245\346\224\266\346\226\207\344\273\266</h3>", nullptr));
        label->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\350\267\257\345\276\204\357\274\232", nullptr));
        editSavePath->setPlaceholderText(QApplication::translate("MainWindow", "\350\257\267\351\200\211\346\213\251\346\216\245\346\224\266\346\226\207\344\273\266\344\277\235\345\255\230\350\267\257\345\276\204", nullptr));
        btnChooseSavePath->setText(QApplication::translate("MainWindow", "\351\200\211\346\213\251", nullptr));
        lblReceiveStatus->setText(QApplication::translate("MainWindow", "\347\212\266\346\200\201\357\274\232\346\234\252\345\274\200\345\247\213\346\216\245\346\224\266", nullptr));
        btnStartReceive->setText(QApplication::translate("MainWindow", "\345\274\200\345\247\213\346\216\245\346\224\266", nullptr));
        btnStopReceive->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242\346\216\245\346\224\266", nullptr));
        label1->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256\351\241\265\351\235\242\357\274\210\350\256\276\345\244\207\345\220\215 / \347\253\257\345\217\243 / \344\277\235\345\255\230\350\267\257\345\276\204\357\274\211", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

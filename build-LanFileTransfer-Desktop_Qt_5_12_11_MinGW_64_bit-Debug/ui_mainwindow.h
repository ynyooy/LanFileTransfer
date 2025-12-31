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
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
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
    QVBoxLayout *verticalLayout_4;
    QLabel *lblSubtitle;
    QFrame *line;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *lblSelection;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnSendFile;
    QPushButton *btnSendFolder;
    QPushButton *btnSendText;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_3;
    QLabel *lblDevicesTitle;
    QPushButton *btnrefresh;
    QSpacerItem *horizontalSpacer_3;
    QListView *fileListView;

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
        sendButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #e0e0e0;\n"
"    border-radius: 8px;\n"
"    background-color: white;\n"
"    padding: 8px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-color: #2196f3;\n"
"    background-color: #f5f9ff;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    border-color: #1976d2;\n"
"    background-color: #e3f2fd;\n"
"}"));

        verticalLayout->addWidget(sendButton);

        settingsButton = new QPushButton(centralwidget);
        settingsButton->setObjectName(QString::fromUtf8("settingsButton"));
        settingsButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #e0e0e0;\n"
"    border-radius: 8px;\n"
"    background-color: white;\n"
"    padding: 8px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-color: #2196f3;\n"
"    background-color: #f5f9ff;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    border-color: #1976d2;\n"
"    background-color: #e3f2fd;\n"
"}"));

        verticalLayout->addWidget(settingsButton);

        receiveButton = new QPushButton(centralwidget);
        receiveButton->setObjectName(QString::fromUtf8("receiveButton"));
        receiveButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #e0e0e0;\n"
"    border-radius: 8px;\n"
"    background-color: white;\n"
"    padding: 8px;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-color: #2196f3;\n"
"    background-color: #f5f9ff;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    border-color: #1976d2;\n"
"    background-color: #e3f2fd;\n"
"}"));

        verticalLayout->addWidget(receiveButton);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        horizontalLayout_4->addLayout(verticalLayout);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        lblSubtitle = new QLabel(centralwidget);
        lblSubtitle->setObjectName(QString::fromUtf8("lblSubtitle"));
        lblSubtitle->setStyleSheet(QString::fromUtf8("\350\267\250\345\271\263\345\217\260\345\261\200\345\237\237\347\275\221\346\226\207\344\273\266\344\274\240\350\276\223"));

        verticalLayout_4->addWidget(lblSubtitle);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        line->setLineWidth(2);

        verticalLayout_4->addWidget(line);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lblSelection = new QLabel(centralwidget);
        lblSelection->setObjectName(QString::fromUtf8("lblSelection"));

        horizontalLayout->addWidget(lblSelection);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnSendFile = new QPushButton(centralwidget);
        btnSendFile->setObjectName(QString::fromUtf8("btnSendFile"));
        btnSendFile->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #eeeeee;\n"
"    border-radius: 8px;\n"
"    background-color: #fafafa;\n"
"    padding: 8px;\n"
"    color: #424242;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-color: #bdbdbd;\n"
"    background-color: #f5f5f5;\n"
"    color: #212121;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    border-color: #9e9e9e;\n"
"    background-color: #eeeeee;\n"
"    color: #212121;\n"
"}"));

        horizontalLayout_2->addWidget(btnSendFile);

        btnSendFolder = new QPushButton(centralwidget);
        btnSendFolder->setObjectName(QString::fromUtf8("btnSendFolder"));
        btnSendFolder->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #eeeeee;\n"
"    border-radius: 8px;\n"
"    background-color: #fafafa;\n"
"    padding: 8px;\n"
"    color: #424242;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-color: #bdbdbd;\n"
"    background-color: #f5f5f5;\n"
"    color: #212121;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    border-color: #9e9e9e;\n"
"    background-color: #eeeeee;\n"
"    color: #212121;\n"
"}"));

        horizontalLayout_2->addWidget(btnSendFolder);

        btnSendText = new QPushButton(centralwidget);
        btnSendText->setObjectName(QString::fromUtf8("btnSendText"));
        btnSendText->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 2px solid #eeeeee;\n"
"    border-radius: 8px;\n"
"    background-color: #fafafa;\n"
"    padding: 8px;\n"
"    color: #424242;\n"
"    font-weight: 500;\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    border-color: #bdbdbd;\n"
"    background-color: #f5f5f5;\n"
"    color: #212121;\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    border-color: #9e9e9e;\n"
"    background-color: #eeeeee;\n"
"    color: #212121;\n"
"}"));

        horizontalLayout_2->addWidget(btnSendText);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lblDevicesTitle = new QLabel(centralwidget);
        lblDevicesTitle->setObjectName(QString::fromUtf8("lblDevicesTitle"));

        horizontalLayout_3->addWidget(lblDevicesTitle);

        btnrefresh = new QPushButton(centralwidget);
        btnrefresh->setObjectName(QString::fromUtf8("btnrefresh"));
        btnrefresh->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: none;\n"
"    border-radius: 10px;\n"
"    background-color: #90caf9;  /* \345\217\230\346\265\205\347\232\204\350\223\235\350\211\262 */\n"
"    width: 20px;\n"
"    height: 20px;\n"
"    min-width: 20px;\n"
"    max-width: 20px;\n"
"    min-height: 20px;\n"
"    max-height: 20px;\n"
"    qproperty-iconSize: 10px;\n"
"    /* \345\255\227\344\275\223\345\222\214\345\233\276\346\240\207\351\242\234\350\211\262\350\260\203\346\225\264\344\270\272\346\265\205\350\211\262 */\n"
"    color: #ffffff;\n"
"    font-size: 8px;  /* \345\246\202\346\236\234\346\234\211\346\226\207\345\255\227\357\274\214\350\260\203\346\225\264\345\255\227\344\275\223\345\244\247\345\260\217 */\n"
"}\n"
"\n"
"QPushButton:hover {\n"
"    background-color: #64b5f6;  /* \346\202\254\345\201\234\346\227\266\347\250\215\345\276\256\346\267\261\344\270\200\347\202\271 */\n"
"}\n"
"\n"
"QPushButton:pressed {\n"
"    background-color: #42a5f5;  /* \346\214\211\344\270\213\346\227\266\346\233\264\346\267\261\344\270\200"
                        "\344\272\233 */\n"
"}"));

        horizontalLayout_3->addWidget(btnrefresh);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_3);

        fileListView = new QListView(centralwidget);
        fileListView->setObjectName(QString::fromUtf8("fileListView"));

        verticalLayout_3->addWidget(fileListView);


        verticalLayout_4->addLayout(verticalLayout_3);


        horizontalLayout_4->addLayout(verticalLayout_4);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "LocalSend", nullptr));
        lblTitle->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:15pt; font-weight:300; color:#2196f3;\">LocalSend</span></p></body></html>", nullptr));
        sendButton->setText(QApplication::translate("MainWindow", "\345\217\221\351\200\201", nullptr));
        settingsButton->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        receiveButton->setText(QApplication::translate("MainWindow", "\346\216\245\346\224\266", nullptr));
        lblSubtitle->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:12pt; color:#555;\">\350\267\250\345\271\263\345\217\260\345\261\200\345\237\237\347\275\221\346\226\207\344\273\266\344\274\240\350\276\223</span></p></body></html>", nullptr));
        lblSelection->setText(QApplication::translate("MainWindow", "<html>\n"
"<head/>\n"
"<body>\n"
"<p align=\"center\">\n"
"  <span style=\"font-size:8pt; font-weight:300; color:#5577AA;\">\n"
"  \351\200\211\346\213\251\345\217\221\351\200\201\345\206\205\345\256\271\n"
"</span>\n"
"</p>\n"
"</body>\n"
"</html>", nullptr));
        btnSendFile->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
        btnSendFolder->setText(QApplication::translate("MainWindow", "\346\226\207\344\273\266\345\244\271", nullptr));
        btnSendText->setText(QApplication::translate("MainWindow", "\346\226\207\346\234\254", nullptr));
        lblDevicesTitle->setText(QApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:8pt; font-weight:200;\">\351\231\204\350\277\221\347\232\204\350\256\276\345\244\207</span></p></body></html>", nullptr));
        btnrefresh->setText(QApplication::translate("MainWindow", "\345\210\267\346\226\260", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

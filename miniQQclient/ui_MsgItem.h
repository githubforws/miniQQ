/********************************************************************************
** Form generated from reading UI file 'MsgItem.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MSGITEM_H
#define UI_MSGITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MsgItem
{
public:
    QGridLayout *gridLayout_2;
    QWidget *widgetMain;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QWidget *widgetHead;
    QVBoxLayout *verticalLayout_3;
    QLabel *lbName;
    QLabel *lbMsg;
    QVBoxLayout *verticalLayout_2;
    QLabel *lbTime;
    QWidget *widgetCount;
    QLabel *lbCount;

    void setupUi(QWidget *MsgItem)
    {
        if (MsgItem->objectName().isEmpty())
            MsgItem->setObjectName("MsgItem");
        MsgItem->resize(150, 50);
        MsgItem->setMinimumSize(QSize(150, 0));
        MsgItem->setMaximumSize(QSize(150, 70));
        gridLayout_2 = new QGridLayout(MsgItem);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        widgetMain = new QWidget(MsgItem);
        widgetMain->setObjectName("widgetMain");
        widgetMain->setMinimumSize(QSize(100, 50));
        widgetMain->setMaximumSize(QSize(999, 50));
        widgetMain->setStyleSheet(QString::fromUtf8("QWidget#widgetMain{\n"
"	background-color: rgb(255, 255, 255);\n"
"	border-bottom: 1px solid #F2F2F2;\n"
"}\n"
"\n"
""));
        gridLayout = new QGridLayout(widgetMain);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        widgetHead = new QWidget(widgetMain);
        widgetHead->setObjectName("widgetHead");
        widgetHead->setMinimumSize(QSize(30, 30));
        widgetHead->setMaximumSize(QSize(30, 30));
        widgetHead->setStyleSheet(QString::fromUtf8("QWidget#widgetHead{\n"
"	background-color: rgb(0, 0, 0);\n"
"	border-radius: 4px;\n"
"	border-image: url(:/image/Head.png);\n"
"}"));

        horizontalLayout->addWidget(widgetHead);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(0);
        verticalLayout_3->setObjectName("verticalLayout_3");
        lbName = new QLabel(widgetMain);
        lbName->setObjectName("lbName");
        lbName->setStyleSheet(QString::fromUtf8("QLabel{\n"
"	background-color: transparent;\n"
"	font: 75 14pt \"Arial\";\n"
"	color: #000000\n"
"}"));

        verticalLayout_3->addWidget(lbName);

        lbMsg = new QLabel(widgetMain);
        lbMsg->setObjectName("lbMsg");
        lbMsg->setStyleSheet(QString::fromUtf8("QLabel#labelMsg{\n"
"	background-color: transparent;\n"
"	font: 75 11pt \"Arial\";\n"
"	color: #888888;\n"
"}"));

        verticalLayout_3->addWidget(lbMsg);


        horizontalLayout->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        lbTime = new QLabel(widgetMain);
        lbTime->setObjectName("lbTime");
        lbTime->setMaximumSize(QSize(50, 16777215));
        lbTime->setStyleSheet(QString::fromUtf8("QLabel#labelTime{\n"
"	background-color: transparent;\n"
"	font: 75 11pt \"Arial\";\n"
"	color: #888888;\n"
"}"));

        verticalLayout_2->addWidget(lbTime);

        widgetCount = new QWidget(widgetMain);
        widgetCount->setObjectName("widgetCount");
        widgetCount->setMinimumSize(QSize(21, 21));
        widgetCount->setMaximumSize(QSize(21, 21));
        widgetCount->setStyleSheet(QString::fromUtf8("QWidget#widgetCount{\n"
"	border-radius: 10px;\n"
"	background-color: rgb(255, 0, 0);\n"
"}"));
        lbCount = new QLabel(widgetCount);
        lbCount->setObjectName("lbCount");
        lbCount->setGeometry(QRect(0, 0, 21, 21));
        lbCount->setStyleSheet(QString::fromUtf8("QLabel#labelCount{\n"
"	color: white;\n"
"	background-color: transparent;\n"
"	font: 10pt \"Airal\";\n"
"}"));
        lbCount->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(widgetCount);


        horizontalLayout->addLayout(verticalLayout_2);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);


        gridLayout_2->addWidget(widgetMain, 0, 0, 1, 1);


        retranslateUi(MsgItem);

        QMetaObject::connectSlotsByName(MsgItem);
    } // setupUi

    void retranslateUi(QWidget *MsgItem)
    {
        MsgItem->setWindowTitle(QCoreApplication::translate("MsgItem", "Form", nullptr));
        lbName->setText(QCoreApplication::translate("MsgItem", "Karson", nullptr));
        lbMsg->setText(QCoreApplication::translate("MsgItem", "How do you do?", nullptr));
        lbTime->setText(QCoreApplication::translate("MsgItem", "09:00", nullptr));
        lbCount->setText(QCoreApplication::translate("MsgItem", "99", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MsgItem: public Ui_MsgItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MSGITEM_H

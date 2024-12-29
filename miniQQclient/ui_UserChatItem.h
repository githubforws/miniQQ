/********************************************************************************
** Form generated from reading UI file 'UserChatItem.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERCHATITEM_H
#define UI_USERCHATITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserChatItem
{
public:
    QGridLayout *gridLayout;
    QListWidget *listWidget;

    void setupUi(QWidget *UserChatItem)
    {
        if (UserChatItem->objectName().isEmpty())
            UserChatItem->setObjectName("UserChatItem");
        UserChatItem->resize(760, 500);
        UserChatItem->setMinimumSize(QSize(760, 500));
        UserChatItem->setMaximumSize(QSize(760, 500));
        gridLayout = new QGridLayout(UserChatItem);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(UserChatItem);
        listWidget->setObjectName("listWidget");
        listWidget->setMinimumSize(QSize(760, 500));
        listWidget->setMaximumSize(QSize(760, 500));
        listWidget->setStyleSheet(QString::fromUtf8("color: rgb(255, 255, 255);"));

        gridLayout->addWidget(listWidget, 0, 0, 1, 1);


        retranslateUi(UserChatItem);

        QMetaObject::connectSlotsByName(UserChatItem);
    } // setupUi

    void retranslateUi(QWidget *UserChatItem)
    {
        UserChatItem->setWindowTitle(QCoreApplication::translate("UserChatItem", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserChatItem: public Ui_UserChatItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERCHATITEM_H

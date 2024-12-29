/********************************************************************************
** Form generated from reading UI file 'UserChatListItem.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERCHATLISTITEM_H
#define UI_USERCHATLISTITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserChatListItem
{
public:
    QGridLayout *gridLayout;
    QListWidget *listWidget;

    void setupUi(QWidget *UserChatListItem)
    {
        if (UserChatListItem->objectName().isEmpty())
            UserChatListItem->setObjectName("UserChatListItem");
        UserChatListItem->resize(170, 400);
        UserChatListItem->setMinimumSize(QSize(170, 400));
        UserChatListItem->setMaximumSize(QSize(170, 16777215));
        gridLayout = new QGridLayout(UserChatListItem);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        listWidget = new QListWidget(UserChatListItem);
        listWidget->setObjectName("listWidget");

        gridLayout->addWidget(listWidget, 0, 0, 1, 1);


        retranslateUi(UserChatListItem);

        QMetaObject::connectSlotsByName(UserChatListItem);
    } // setupUi

    void retranslateUi(QWidget *UserChatListItem)
    {
        UserChatListItem->setWindowTitle(QCoreApplication::translate("UserChatListItem", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class UserChatListItem: public Ui_UserChatListItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERCHATLISTITEM_H

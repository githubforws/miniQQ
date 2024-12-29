/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <InputMessageItem.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>
#include <SearchUser.h>
#include <UserChatItem.h>
#include <UserChatListItem.h>
#include <UserMenuItem.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_all;
    QGridLayout *gridLayout_3;
    UserChatItem *UserChatItemwidget;
    InputMessageItem *InputMessageItemwidget;
    UserMenuItem *UserMenuItemwidget;
    QGridLayout *gridLayout_4;
    SearchUser *SearchUserwidget;
    UserChatListItem *UserChatListItemwidget;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(980, 800);
        MainWindow->setMinimumSize(QSize(980, 800));
        MainWindow->setMaximumSize(QSize(980, 800));
        MainWindow->setStyleSheet(QString::fromUtf8(""));
        MainWindow->setDockNestingEnabled(false);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        centralwidget->setMinimumSize(QSize(490, 0));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setSizeConstraint(QLayout::SizeConstraint::SetMaximumSize);
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout_all = new QGridLayout();
        gridLayout_all->setSpacing(0);
        gridLayout_all->setObjectName("gridLayout_all");
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName("gridLayout_3");
        UserChatItemwidget = new UserChatItem(centralwidget);
        UserChatItemwidget->setObjectName("UserChatItemwidget");
        UserChatItemwidget->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(UserChatItemwidget, 0, 0, 1, 1);

        InputMessageItemwidget = new InputMessageItem(centralwidget);
        InputMessageItemwidget->setObjectName("InputMessageItemwidget");
        InputMessageItemwidget->setMinimumSize(QSize(0, 300));
        InputMessageItemwidget->setMaximumSize(QSize(16777215, 300));
        InputMessageItemwidget->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(InputMessageItemwidget, 1, 0, 1, 1);


        gridLayout_all->addLayout(gridLayout_3, 0, 2, 1, 1);

        UserMenuItemwidget = new UserMenuItem(centralwidget);
        UserMenuItemwidget->setObjectName("UserMenuItemwidget");
        UserMenuItemwidget->setMinimumSize(QSize(50, 0));
        UserMenuItemwidget->setMaximumSize(QSize(50, 16777215));
        UserMenuItemwidget->setStyleSheet(QString::fromUtf8(""));

        gridLayout_all->addWidget(UserMenuItemwidget, 0, 0, 1, 1);

        gridLayout_4 = new QGridLayout();
        gridLayout_4->setSpacing(0);
        gridLayout_4->setObjectName("gridLayout_4");
        gridLayout_4->setSizeConstraint(QLayout::SizeConstraint::SetDefaultConstraint);
        SearchUserwidget = new SearchUser(centralwidget);
        SearchUserwidget->setObjectName("SearchUserwidget");
        SearchUserwidget->setMinimumSize(QSize(170, 0));
        SearchUserwidget->setMaximumSize(QSize(170, 16777215));
        SearchUserwidget->setStyleSheet(QString::fromUtf8(""));

        gridLayout_4->addWidget(SearchUserwidget, 0, 0, 1, 1);

        UserChatListItemwidget = new UserChatListItem(centralwidget);
        UserChatListItemwidget->setObjectName("UserChatListItemwidget");
        UserChatListItemwidget->setMinimumSize(QSize(170, 0));
        UserChatListItemwidget->setMaximumSize(QSize(170, 16777215));

        gridLayout_4->addWidget(UserChatListItemwidget, 1, 0, 1, 1);


        gridLayout_all->addLayout(gridLayout_4, 0, 1, 1, 1);


        gridLayout->addLayout(gridLayout_all, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "miniQQ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'UserMenuItem.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_USERMENUITEM_H
#define UI_USERMENUITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_UserMenuItem
{
public:
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_2;
    QGridLayout *gridLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QSpacerItem *verticalSpacer_2;

    void setupUi(QWidget *UserMenuItem)
    {
        if (UserMenuItem->objectName().isEmpty())
            UserMenuItem->setObjectName("UserMenuItem");
        UserMenuItem->resize(50, 554);
        UserMenuItem->setMinimumSize(QSize(50, 400));
        UserMenuItem->setMaximumSize(QSize(50, 16777215));
        gridLayout_2 = new QGridLayout(UserMenuItem);
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        pushButton = new QPushButton(UserMenuItem);
        pushButton->setObjectName("pushButton");
        pushButton->setMinimumSize(QSize(50, 50));
        pushButton->setMaximumSize(QSize(50, 50));
        pushButton->setStyleSheet(QString::fromUtf8("image: url(:/icon/defaultheadpicture.jpg);"));

        gridLayout->addWidget(pushButton, 0, 0, 1, 1);

        pushButton_2 = new QPushButton(UserMenuItem);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setMinimumSize(QSize(50, 50));
        pushButton_2->setMaximumSize(QSize(50, 50));
        pushButton_2->setStyleSheet(QString::fromUtf8("image: url(:/icon/chat.jpg);"));

        gridLayout->addWidget(pushButton_2, 1, 0, 1, 1);

        pushButton_3 = new QPushButton(UserMenuItem);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setMinimumSize(QSize(50, 50));
        pushButton_3->setMaximumSize(QSize(50, 50));
        pushButton_3->setStyleSheet(QString::fromUtf8("image: url(:/icon/setting.jpg);"));

        gridLayout->addWidget(pushButton_3, 2, 0, 1, 1);


        verticalLayout_2->addLayout(gridLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        gridLayout_2->addLayout(verticalLayout_2, 0, 0, 1, 1);


        retranslateUi(UserMenuItem);

        QMetaObject::connectSlotsByName(UserMenuItem);
    } // setupUi

    void retranslateUi(QWidget *UserMenuItem)
    {
        UserMenuItem->setWindowTitle(QCoreApplication::translate("UserMenuItem", "Form", nullptr));
        pushButton->setText(QString());
        pushButton_2->setText(QString());
        pushButton_3->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class UserMenuItem: public Ui_UserMenuItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_USERMENUITEM_H

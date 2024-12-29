/********************************************************************************
** Form generated from reading UI file 'SearchUser.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SEARCHUSER_H
#define UI_SEARCHUSER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SearchUser
{
public:
    QGridLayout *gridLayout;
    QGridLayout *gridLayout_3;
    QGridLayout *gridLayout_2;
    QLineEdit *InputUserIdlineEdit;
    QPushButton *SearchpushButton;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *SearchUser)
    {
        if (SearchUser->objectName().isEmpty())
            SearchUser->setObjectName("SearchUser");
        SearchUser->resize(458, 28);
        SearchUser->setMinimumSize(QSize(0, 24));
        SearchUser->setMaximumSize(QSize(16777215, 28));
        SearchUser->setSizeIncrement(QSize(0, 0));
        gridLayout = new QGridLayout(SearchUser);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(0);
        gridLayout_3->setObjectName("gridLayout_3");
        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(0);
        gridLayout_2->setObjectName("gridLayout_2");
        InputUserIdlineEdit = new QLineEdit(SearchUser);
        InputUserIdlineEdit->setObjectName("InputUserIdlineEdit");
        InputUserIdlineEdit->setMinimumSize(QSize(0, 24));
        InputUserIdlineEdit->setMaximumSize(QSize(16777215, 20));

        gridLayout_2->addWidget(InputUserIdlineEdit, 0, 0, 1, 1);

        SearchpushButton = new QPushButton(SearchUser);
        SearchpushButton->setObjectName("SearchpushButton");
        SearchpushButton->setMinimumSize(QSize(24, 24));
        SearchpushButton->setMaximumSize(QSize(24, 24));
        SearchpushButton->setStyleSheet(QString::fromUtf8("image: url(:/icon/search.jpg);"));

        gridLayout_2->addWidget(SearchpushButton, 0, 1, 1, 1);


        gridLayout_3->addLayout(gridLayout_2, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(0, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        gridLayout_3->addItem(horizontalSpacer, 0, 1, 1, 1);


        gridLayout->addLayout(gridLayout_3, 0, 0, 1, 1);


        retranslateUi(SearchUser);

        QMetaObject::connectSlotsByName(SearchUser);
    } // setupUi

    void retranslateUi(QWidget *SearchUser)
    {
        SearchUser->setWindowTitle(QCoreApplication::translate("SearchUser", "Form", nullptr));
        SearchpushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class SearchUser: public Ui_SearchUser {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SEARCHUSER_H

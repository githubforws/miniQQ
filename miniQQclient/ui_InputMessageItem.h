/********************************************************************************
** Form generated from reading UI file 'InputMessageItem.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_INPUTMESSAGEITEM_H
#define UI_INPUTMESSAGEITEM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_InputMessageItem
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_all;
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *ExpressionpushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *FilepushButton;
    QSpacerItem *horizontalSpacer_2;
    QTextEdit *InputMessagetextEdit;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *SendMessagepushButton;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *InputMessageItem)
    {
        if (InputMessageItem->objectName().isEmpty())
            InputMessageItem->setObjectName("InputMessageItem");
        InputMessageItem->setWindowModality(Qt::WindowModality::NonModal);
        InputMessageItem->resize(568, 374);
        InputMessageItem->setMinimumSize(QSize(300, 100));
        gridLayout = new QGridLayout(InputMessageItem);
        gridLayout->setSpacing(0);
        gridLayout->setObjectName("gridLayout");
        gridLayout->setContentsMargins(0, 0, 0, 0);
        verticalLayout_all = new QVBoxLayout();
        verticalLayout_all->setSpacing(0);
        verticalLayout_all->setObjectName("verticalLayout_all");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName("verticalLayout");
        widget = new QWidget(InputMessageItem);
        widget->setObjectName("widget");
        verticalLayout_2 = new QVBoxLayout(widget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName("horizontalLayout");
        ExpressionpushButton = new QPushButton(widget);
        ExpressionpushButton->setObjectName("ExpressionpushButton");
        ExpressionpushButton->setMinimumSize(QSize(30, 30));
        ExpressionpushButton->setMaximumSize(QSize(30, 30));
        ExpressionpushButton->setStyleSheet(QString::fromUtf8("image: url(:/icon/expression.jpg);"));

        horizontalLayout->addWidget(ExpressionpushButton);

        horizontalSpacer = new QSpacerItem(10, 10, QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        FilepushButton = new QPushButton(widget);
        FilepushButton->setObjectName("FilepushButton");
        FilepushButton->setMinimumSize(QSize(30, 30));
        FilepushButton->setMaximumSize(QSize(30, 30));
        FilepushButton->setStyleSheet(QString::fromUtf8("image: url(:/icon/file.jpg);"));

        horizontalLayout->addWidget(FilepushButton);

        horizontalSpacer_2 = new QSpacerItem(10000, 10, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_2->addLayout(horizontalLayout);

        InputMessagetextEdit = new QTextEdit(widget);
        InputMessagetextEdit->setObjectName("InputMessagetextEdit");
        InputMessagetextEdit->setInputMethodHints(Qt::InputMethodHint::ImhMultiLine);

        verticalLayout_2->addWidget(InputMessagetextEdit);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalSpacer_4 = new QSpacerItem(100, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        SendMessagepushButton = new QPushButton(widget);
        SendMessagepushButton->setObjectName("SendMessagepushButton");
        SendMessagepushButton->setMinimumSize(QSize(70, 50));
        SendMessagepushButton->setMaximumSize(QSize(70, 50));

        horizontalLayout_2->addWidget(SendMessagepushButton);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addWidget(widget);


        verticalLayout_all->addLayout(verticalLayout);


        gridLayout->addLayout(verticalLayout_all, 0, 0, 1, 1);


        retranslateUi(InputMessageItem);

        QMetaObject::connectSlotsByName(InputMessageItem);
    } // setupUi

    void retranslateUi(QWidget *InputMessageItem)
    {
        InputMessageItem->setWindowTitle(QCoreApplication::translate("InputMessageItem", "Form", nullptr));
        ExpressionpushButton->setText(QString());
        FilepushButton->setText(QString());
        SendMessagepushButton->setText(QCoreApplication::translate("InputMessageItem", "\345\217\221\351\200\201", nullptr));
    } // retranslateUi

};

namespace Ui {
    class InputMessageItem: public Ui_InputMessageItem {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_INPUTMESSAGEITEM_H

/********************************************************************************
** Form generated from reading UI file 'register.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTER_H
#define UI_REGISTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Register
{
public:
    QWidget *widget;
    QLineEdit *NameInputRegisterlineEdit;
    QLineEdit *PasswdInputRegisterlineEdit;
    QLineEdit *PasswdInputReRegisterlineEdit;
    QPushButton *RegisterpushButton;
    QLabel *WelcomeRegisterLabel;

    void setupUi(QWidget *Register)
    {
        if (Register->objectName().isEmpty())
            Register->setObjectName("Register");
        Register->resize(400, 500);
        Register->setMinimumSize(QSize(400, 500));
        Register->setMaximumSize(QSize(400, 500));
        Register->setStyleSheet(QString::fromUtf8("background-image: url(:/images/background.jpg);"));
        widget = new QWidget(Register);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(-10, 0, 431, 501));
        widget->setStyleSheet(QString::fromUtf8(""));
        NameInputRegisterlineEdit = new QLineEdit(widget);
        NameInputRegisterlineEdit->setObjectName("NameInputRegisterlineEdit");
        NameInputRegisterlineEdit->setGeometry(QRect(90, 200, 241, 31));
        PasswdInputRegisterlineEdit = new QLineEdit(widget);
        PasswdInputRegisterlineEdit->setObjectName("PasswdInputRegisterlineEdit");
        PasswdInputRegisterlineEdit->setGeometry(QRect(90, 250, 241, 31));
        PasswdInputRegisterlineEdit->setEchoMode(QLineEdit::EchoMode::Password);
        PasswdInputReRegisterlineEdit = new QLineEdit(widget);
        PasswdInputReRegisterlineEdit->setObjectName("PasswdInputReRegisterlineEdit");
        PasswdInputReRegisterlineEdit->setGeometry(QRect(90, 300, 241, 31));
        PasswdInputReRegisterlineEdit->setEchoMode(QLineEdit::EchoMode::Password);
        RegisterpushButton = new QPushButton(widget);
        RegisterpushButton->setObjectName("RegisterpushButton");
        RegisterpushButton->setGeometry(QRect(90, 350, 241, 41));
        WelcomeRegisterLabel = new QLabel(widget);
        WelcomeRegisterLabel->setObjectName("WelcomeRegisterLabel");
        WelcomeRegisterLabel->setGeometry(QRect(10, 0, 411, 201));
        WelcomeRegisterLabel->setStyleSheet(QString::fromUtf8("font: 9pt \"\345\215\216\346\226\207\345\275\251\344\272\221\";"));
        WelcomeRegisterLabel->setFrameShape(QFrame::Shape::NoFrame);

        retranslateUi(Register);

        QMetaObject::connectSlotsByName(Register);
    } // setupUi

    void retranslateUi(QWidget *Register)
    {
        Register->setWindowTitle(QCoreApplication::translate("Register", "miniQQ", nullptr));
        NameInputRegisterlineEdit->setPlaceholderText(QCoreApplication::translate("Register", "\350\276\223\345\205\245\346\230\265\347\247\260", nullptr));
        PasswdInputRegisterlineEdit->setPlaceholderText(QCoreApplication::translate("Register", "\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        PasswdInputReRegisterlineEdit->setPlaceholderText(QCoreApplication::translate("Register", "\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        RegisterpushButton->setText(QCoreApplication::translate("Register", "\347\253\213\345\215\263\346\263\250\345\206\214", nullptr));
        WelcomeRegisterLabel->setText(QCoreApplication::translate("Register", "<html><head/><body><p><span style=\" font-size:18pt;\">miniQQ</span></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><br/></p><p align=\"center\"><span style=\" font-size:28pt;\">\346\254\242\350\277\216\346\263\250\345\206\214miniQQ</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Register: public Ui_Register {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTER_H

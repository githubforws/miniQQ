/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Login
{
public:
    QWidget *widget;
    QPushButton *LoginLoginButton;
    QPushButton *LoginRegisterButton;
    QLineEdit *AccountNumberInputLoginlineEdit;
    QLineEdit *PasswdInputLoginlineEdit;
    QLabel *label;

    void setupUi(QWidget *Login)
    {
        if (Login->objectName().isEmpty())
            Login->setObjectName("Login");
        Login->resize(300, 400);
        Login->setMinimumSize(QSize(300, 400));
        Login->setMaximumSize(QSize(300, 400));
        Login->setAutoFillBackground(false);
        Login->setStyleSheet(QString::fromUtf8("background-image: url(:/images/background.jpg);"));
        widget = new QWidget(Login);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 301, 401));
        widget->setStyleSheet(QString::fromUtf8(""));
        LoginLoginButton = new QPushButton(widget);
        LoginLoginButton->setObjectName("LoginLoginButton");
        LoginLoginButton->setGeometry(QRect(60, 240, 71, 41));
        LoginRegisterButton = new QPushButton(widget);
        LoginRegisterButton->setObjectName("LoginRegisterButton");
        LoginRegisterButton->setGeometry(QRect(170, 240, 71, 41));
        AccountNumberInputLoginlineEdit = new QLineEdit(widget);
        AccountNumberInputLoginlineEdit->setObjectName("AccountNumberInputLoginlineEdit");
        AccountNumberInputLoginlineEdit->setGeometry(QRect(40, 160, 221, 31));
        AccountNumberInputLoginlineEdit->setEchoMode(QLineEdit::EchoMode::Normal);
        PasswdInputLoginlineEdit = new QLineEdit(widget);
        PasswdInputLoginlineEdit->setObjectName("PasswdInputLoginlineEdit");
        PasswdInputLoginlineEdit->setGeometry(QRect(40, 200, 221, 31));
        PasswdInputLoginlineEdit->setEchoMode(QLineEdit::EchoMode::Password);
        label = new QLabel(widget);
        label->setObjectName("label");
        label->setGeometry(QRect(0, 0, 301, 151));
        QFont font;
        font.setFamilies({QString::fromUtf8("\345\215\216\346\226\207\345\275\251\344\272\221")});
        font.setPointSize(20);
        label->setFont(font);
        label->setStyleSheet(QString::fromUtf8(""));
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        retranslateUi(Login);

        QMetaObject::connectSlotsByName(Login);
    } // setupUi

    void retranslateUi(QWidget *Login)
    {
        Login->setWindowTitle(QCoreApplication::translate("Login", "miniQQ", nullptr));
        LoginLoginButton->setText(QCoreApplication::translate("Login", "\347\231\273\345\275\225", nullptr));
        LoginRegisterButton->setText(QCoreApplication::translate("Login", "\346\263\250\345\206\214", nullptr));
        AccountNumberInputLoginlineEdit->setPlaceholderText(QCoreApplication::translate("Login", "\350\257\267\350\276\223\345\205\245\350\264\246\345\217\267", nullptr));
        PasswdInputLoginlineEdit->setPlaceholderText(QCoreApplication::translate("Login", "\350\257\267\350\276\223\345\205\245\345\257\206\347\240\201", nullptr));
        label->setText(QCoreApplication::translate("Login", "miniQQ", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Login: public Ui_Login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H

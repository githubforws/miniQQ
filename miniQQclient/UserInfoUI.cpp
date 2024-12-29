#include "UserInfoUI.h"
#include "ui_UserInfoUI.h"

UserInfoUI::UserInfoUI(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserInfoUI)
{
    ui->setupUi(this);
}

UserInfoUI::~UserInfoUI()
{
    delete ui;
}

void UserInfoUI::SetUserInfoSlot(QString id,QString name,QString passwd){
    QString idlabel = "账号：" + id;
    //QString namelabel = "昵称：" + name;
    //QString passwdlabel = "密码：";
    ui->UserIDlabel->setText(idlabel);
    ui->namelineEdit->setText(name);
    ui->passwdlineEdit->setText(passwd);
    this->show();
}

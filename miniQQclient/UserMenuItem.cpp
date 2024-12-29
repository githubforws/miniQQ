#include "UserMenuItem.h"
#include "ui_UserMenuItem.h"
#include <QDebug>

UserMenuItem::UserMenuItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserMenuItem)
{
    ui->setupUi(this);
    ui->pushButton->setCheckable(true);
    ui->pushButton_2->setCheckable(true);
    ui->pushButton_3->setCheckable(true);

    this->userinfoui = new UserInfoUI();
    connect(this,SIGNAL(SetUserInfoSignal(QString,QString,QString)),this->userinfoui,SLOT(SetUserInfoSlot(QString,QString,QString)));
}

UserMenuItem::~UserMenuItem()
{
    delete ui;
}

///
/// \brief UserMenuItem::on_pushButton_clicked 点击头像显示本客户端信息
///
void UserMenuItem::on_pushButton_clicked()
{
    qDebug()<<"UserMenuItem::on_pushButton_clicked  点击了头像";
    emit GetUserInfoSignal();
    //userinfoui->show();
}

void UserMenuItem::ShowUserInfoSlot(QString id,QString name,QString passwd){
    emit SetUserInfoSignal(id,name,passwd);
}


void UserMenuItem::on_pushButton_2_clicked()
{
    qDebug()<<"UserMenuItem::on_pushButton_clicked  点击了消息";
}


void UserMenuItem::on_pushButton_3_clicked()
{
    qDebug()<<"UserMenuItem::on_pushButton_clicked  点击了设置";
}

void UserMenuItem::test(){
    qDebug()<<"UserMenuItem::test()";
}

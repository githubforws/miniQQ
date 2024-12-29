#include "register.h"
#include "ui_register.h"
#include <QMessageBox>

Register::Register(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Register)
{
    ui->setupUi(this);
    connect(ui->PasswdInputReRegisterlineEdit,SIGNAL(returnPressed()),this,SLOT(on_RegisterpushButton_clicked()));//在密码框按下回车==点击登录
}

Register::~Register()
{
    delete ui;
}

///
/// \brief Register::RegisterRequestSlot
///发送注册请求信号
///
void Register::RegisterRequestSlot(){
    emit RegisterRequest();
}

///
/// \brief Register::on_RegisterpushButton_clicked
///当点击立即注册按钮时接收昵称密码等信息并进行验证，将验证后的信息发送给MainWindow进行处理
///
void Register::on_RegisterpushButton_clicked()
{
    NameR = ui->NameInputRegisterlineEdit->text().trimmed();//昵称
    PasswdR = ui->PasswdInputRegisterlineEdit->text().trimmed();//密码
    PasswdReR = ui->PasswdInputReRegisterlineEdit->text().trimmed();//确认密码
    if(NameR.isEmpty()){
        NameR.clear();
        PasswdR.clear();
        PasswdReR.clear();
        ui->PasswdInputReRegisterlineEdit->clear();
        ui->PasswdInputRegisterlineEdit->clear();
        ui->NameInputRegisterlineEdit->clear();
        QMessageBox().information(NULL,"error","昵称不可为空");
        return;
    }
    if(PasswdR.length()<INPUTMINLENTH){
        NameR.clear();
        PasswdR.clear();
        PasswdReR.clear();
        ui->PasswdInputReRegisterlineEdit->clear();
        ui->PasswdInputRegisterlineEdit->clear();
        ui->NameInputRegisterlineEdit->clear();
        QMessageBox().information(NULL,"error","密码长度不小于6位");
        return;
    }
    if(PasswdR.compare(PasswdReR)){
        NameR.clear();
        PasswdR.clear();
        PasswdReR.clear();
        ui->PasswdInputReRegisterlineEdit->clear();
        ui->PasswdInputRegisterlineEdit->clear();
        ui->NameInputRegisterlineEdit->clear();
        QMessageBox().information(NULL,"error","输入的两次密码不同");
        return;
    }
    RegisterRequestSlot();

    qDebug()<<"向主函数发送了注册请求";
}

///
/// \brief Register::GetName
/// \return
///获取昵称
///
QString Register::GetName(){
    return this->NameR;
}

///
/// \brief Register::GetPasswd
/// \return
///获取密码
///
QString Register::GetPasswd(){
    return this->PasswdR;
}

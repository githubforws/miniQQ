#include "login.h"
#include "ui_login.h"
#include "register.h"

#include <QRegularExpressionValidator>
#include <QPushButton>
#include <QMessageBox>
#include <QStyleOption>
#include <QDebug>

Login::Login(QWidget *parent)
    : QWidget(parent)
    ,ui(new Ui::Login)
{
    ui->setupUi(this);

    ui->AccountNumberInputLoginlineEdit->setValidator(new QRegularExpressionValidator(QRegularExpression ("[0-9]+$")));//仅允许输入数字
    ui->AccountNumberInputLoginlineEdit->setMaxLength(INPUTMAXLENTH);//限制账号框输入最大长度为20
    ui->PasswdInputLoginlineEdit->setMaxLength(INPUTMAXLENTH);//限制密码框输入最大长度为20
    //connect(ui->PasswdInputLoginlineEdit,SIGNAL(returnPressed()),this,SLOT(on_LoginLoginButton_clicked()));//在密码框按下回车==点击登录
    //这里按下回车跳到的on_LoginLoginButton_clicked并没有给主界面发送信号，手动发信号会与下面的connect重复发两次信号，不知道会不会产生bug
    connect(ui->LoginLoginButton,&QPushButton::clicked,this,&Login::LonginRequestSlot);//当点击登录按钮时向主界面发送一个信号，对账号密码进行验证
    connect(ui->LoginRegisterButton,&QPushButton::clicked,this,&Login::RegisterRequestSlot);//当点击登录按钮时向主界面发送一个信号，接收Register对象
}

Login::~Login()
{
    delete ui;
}

///
/// \brief Login::on_LoginRegisterButton_clicked
///事件：点击注册按钮
///显示注册界面
///
void Login::on_LoginRegisterButton_clicked()
{
    this->RegisterInterface = new Register();//实例化注册界面
    this->RegisterInterface->show();//显示注册界面
    qDebug()<<"向主界面发送一个点击注册按钮的信号";
    //RegisterRequestSlot();//发送注册Register信号
}

///
/// \brief Login::on_LoginLoginButton_clicked
/// 事件：点击注册按钮
/// 将账号框和密码框内的内容赋给accountnum和passwd
///
void Login::on_LoginLoginButton_clicked()
{
    accountnum = ui->AccountNumberInputLoginlineEdit->text().trimmed();//获取账号框内容并去除多余空格
    passwd = ui->PasswdInputLoginlineEdit->text().trimmed();//获取密码框内容并去除多余空格
    //账号或密码长度小于6位
    if(accountnum.isEmpty() || passwd.length()<INPUTMINLENTH){
        //清空账号密码
        accountnum.clear();
        passwd.clear();
        //清空输入框
        ui->AccountNumberInputLoginlineEdit->clear();
        ui->PasswdInputLoginlineEdit->clear();
        QMessageBox().information(NULL,"error","账号或密码长度至少为6位数");
        return;
    }
    qDebug()<<"向主界面发送一个点击登录按钮的信号";
    //LonginRequestSlot();//发送登录信号
}

///
/// 获取账号
///
QString Login::GetAccountnumber(){

    return this->accountnum;
}

///
///获取密码
///
QString Login::GetPasswd(){
    return this->passwd;
}

///
/// \brief Login::LonginRequestSlot
///向主界面发送一个信号，使其接收账号密码并进行验证
void Login::LonginRequestSlot(){
    emit LonginRequest();
}

///
/// \brief RegisterRequestSlot
///向主界面发送注册界面实例化信号，使其接收注册界面对象
///
void Login::RegisterRequestSlot(){
    emit RegisterInstantiate();
}

///
/// \brief Login::GetRegister
/// \return
///返回Register对象
///
Register * Login::GetRegister(){
    return this->RegisterInterface;
}

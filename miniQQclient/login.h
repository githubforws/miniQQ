///Login类
/// 注册界面
/// 控件：账号输入框，密码输入框，登录按钮，注册按钮
/// 点击登录按钮时向MainWindow类发送一个验证信号，使其对登录的账号密码进行验证
/// 点击注册按钮时向MainWindow类发送一个接收信号，使其接收Register类，并接受注册信息
///

#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "register.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

signals:
    void LonginRequest();//点击登录后向MainWindow类发送信号，验证账号密码
    void RegisterInstantiate();//点击注册按钮时向MainWindow类发送信号，接收注册窗口对象

private slots:
    void on_LoginRegisterButton_clicked();//接收点击注册按钮信号

    void on_LoginLoginButton_clicked();//接收点击登录按钮信号


private:
    Ui::Login *ui;//ui界面

private:
#define INPUTMAXLENTH 20//输入框输入最大长度
#define INPUTMINLENTH 6//输入框输入最小长度
    QString accountnum;//登录账号
    QString passwd;//登录密码

public:
    Register *RegisterInterface=NULL;//注册界面
    QString GetAccountnumber();//获取账号框内容
    QString GetPasswd();//获取密码框内容
    void LonginRequestSlot();//emit发送登录请求信号
    void RegisterRequestSlot();//emit发送创建注册界面信号
    Register * GetRegister();//获取Register对象
    //void paintEvent(QPaintEvent *e);//重写绘画函数，绘制背景

};

#endif // LOGIN_H

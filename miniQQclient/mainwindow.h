#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "login.h"
#include "register.h"
#include "Socket.h"
#include "User.h"
#include "ChatMessage.h"
#include <QListWidgetItem>
#include "UserChatListItem.h"
#include "UserChatItem.h"
#include "UserMenuItem.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    //QString BuildMessage(int,QString,QString,QString,QString,QString);
    void dealMessageTime(QString curMsgTime);//气泡时间
    void dealMessage(ChatMessage *messageW, QListWidgetItem *item, QString text, QString time, ChatMessage::User_Type type);//气泡框
    void ConnectClient();
    ~MainWindow();

public:
    Login *LoginInterface = NULL;//登录界面
    Register *RegisterInterface = NULL;//注册界面，这个界面不由此类实例化，只接受来自Login类的实例化的对象
    QString LoginAccountNumber;//保存登录界面输入的账号
    QString LoginPasswd;//保存登录界面输入的密码
    QString RegisterName;//保存注册界面输入的昵称
    QString RegisterPasswd;//保存注册界面输入的密码

private:
    Ui::MainWindow *ui;
    Socket *client = nullptr;//socket
    User *user = nullptr;//用户
    bool connected = false;//已连接过connect
    UserChatListItem* UserList=nullptr;//用户列表
    UserMenuItem *UserMenu=nullptr;
    //UserChatItem* UserChat=nullptr;//聊天消息框
    //void paintEvent(QPaintEvent *event);

private slots:
    void Verify();//接受并验证登录的账号密码
    void ReceiveRgister();//接收Register对象
    void RegisterRequestSlots();//接收来自Register类的注册信号，对注册信息进行验证
    void SetMessageSlot();//接收文本输入框中输入的信息并构造消息
    void ShowMeInputMessageSlot();//展示我输进去的信息
    void ShowMainSlot();//显示主界面
    void LoginErrorAccountnumSlot();//账号错误登录失败
    void LoginErrorPasswdSlot();//密码错误登录失败
    void UpdateUserListSlot();//更新好友列表
    void NewMessageCountSlot(QString);//来自好友？的一条未读消息
    void ShowNewMessageSlot(QString,QString);//来自好友的一条消息，将其显示在对应的聊天窗口
    void SearchUIDSlotl(QString);//添加好友信号
    void GetUserInfoSlot();//获取用户信息信号

signals:
    void DefaultSignal(QListWidgetItem*);//默认选中第一个好友的信号
    void NewMessageCountSignal(QString);//转发--好友的一条新消息，更新消息数
    void test();
    void UserInfoSignal(QString,QString,QString);//转发用户信息
};
#endif // MAINWINDOW_H

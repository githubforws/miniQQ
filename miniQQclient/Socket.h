#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <QJsonObject>
#include "User.h"

///
/// \brief The Socket class
/// socket通信类
/// 实现对消息数据的处理
///
class Socket:public QObject//,public QTcpSocket
{
    Q_OBJECT

public slots:
    void testSlots();
    void RecvMessageSlots();//接收消息
    void SendMessageSlots(QString);//发送消息
    void displayError(QAbstractSocket::SocketError socketError);
    void AgreeFriendRequestSlot();//点击同意好友申请
    void DisagreeFriendRequestSlot();//不同意
    void test();

private:
    QTcpSocket *client;
    qint16 PORT = 8888;//端口号
    QString IP = "8.137.51.107";//ip地址
    User *user = nullptr;


private:
    //自定义的消息结构
    struct Message
    {
        int CODE;         // 操作码
        QString fromwho;  // 谁发来的
        QString towho;	  // 发给谁
        QString timeis;	  // 发送的时间
        QString password; // 发送者的输入的密码，特殊事件使用，如注册登录等
        QString content;  // 消息内容
        QString buffer;	  // 源消息
    };

private:
         //服务器端对应的操作码
#define REGIST 1001//注册
#define LOGIN 1002//登录
#define ADDFRIENDREQUEST 1003//添加好友请求
#define SENDMSG 1004//发送消息
#define DELFRIEND 1005////删除好友
#define RETURNFRIENDREQUEST 1006//回应好友请求

private:
         //客户端对应的响应操作码
#define TEST 2000
#define AGREEWITHFRIENDREQUEST 2001//同意好友请求
#define LOGINSUCCESFUL 2002//登录成功
#define LOGINERRORACCOUNTNUM 2003//登录失败账号错误
#define LOGINERRORPASSWD 2004//登录失败密码错误
#define REGISTERSUCCESFUL 2005//注册成功
#define UPDATEFRIEND 2006//更新好友信息
#define NEWFRIENDMESSAGE 1004//来自好友的新消息//使用相同信号量，服务器直接转发的消息，修改麻烦
#define SENDADDFRIENDSUCCES 2007//发送添加好友信息成功

private:
    //构建消息
    const char *SetCode = "{\"CODE\":\"";
    const char *SetFromwho = "\",\"fromwho\":\"";
    const char *SetTowho = "\",\"towho\":\"";
    const char *SetTime = "\",\"timeis\":\"";
    const char *SetPassword = "\",\"password\":\"";
    const char *SetContent = "\",\"content\":\"";
    const char *SetEnd = "\"}\0";

public:
    Socket();
    QString SetMessage(int,QString,QString,QString,QString,QString);//构造消息
    void MessageAnalysis(Message msg);//消息分析函数，根据操作码执行不同的操作
    void SetUser(User *user);
    ~Socket();


signals:
    void LoginSuccesSignal();//登录成功信号
    void LoginErrorAccountnumSignal();//登录失败，账号错误信号
    void LoginErrorpasswdSignal();//登录失败，密码错误信号
    void RegisterSuccesSignal();//注册成功信号
    void UpdateFriendInfoSignal();//更新好友列表信号
    void NewMessageCountSignal(QString);//有一条新消息，更新未读消息数,好友id
    void ShowNewMessageSignal(QString,QString);//在对应好友聊天界面显示消息内容，好友id，消息内容
};



#endif // SOCKET_H

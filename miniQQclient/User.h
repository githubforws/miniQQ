#ifndef USER_H
#define USER_H
#include <QObject>

///
/// \brief The User class
/// User类
/// 保存有用户的信息
///
class User:public QObject
{
    Q_OBJECT

public:
    struct FRIEND{
        QString FriendID;//好友id，作为通信的关键信息
        QString FriendName;//好友昵称，显示在好友列表
        QString FriendHeadIco;//好友头像路径
    };
    QVector<FRIEND> FriendList;//用户好友列表

private:
    QString UserID = NULL;//用户ID
    QString UserName = NULL;//用户昵称
    QString UserPasswd = NULL;//用户密码

public:
    User();
    void SetUserinfo(const QString id,const QString Passwd);//设置用户id和密码，登录时使用的
    void SetUserinfo(QString id,QString Passwd,QString name);//设置用户id密码昵称，注册账号时使用的
    void SetUserName(QString name);//设置昵称时使用的，登录时从服务器获取昵称，或修改昵称
    void SetFriendInfo(QString id,QString name);//更新好友列表时更新好友信息
    void SetFriendHPPath(QString id,QString path);//设置好友头像位置
    bool FindFriend(QString);//查找是否已有该好友，true有  false无
    QString GetUserID();//获取用户id
    QString GetUserName(){return UserName;}
    QString GetPasswd(){return UserPasswd;}
    //QVector<FRIEND>* GetFriendList();
    void test();//测试，打印好友信息
    QString NewFriendRequestID;
};
#endif // USER_H

#include "User.h"
#include <QDebug>

User::User() {}


void User::SetUserinfo(const QString id,const QString Passwd){
    qDebug()<<"User::SetUserinfo:"<<id<<Passwd;
    this->UserID = id;
    qDebug()<<"id:"<<this->UserID;
    this->UserPasswd = Passwd;
    qDebug()<<"passwd:"<<this->UserPasswd;
}

void User::SetUserinfo(QString id,QString Passwd,QString name){
    this->UserID = id;
    this->UserPasswd = Passwd;
    this->UserName = name;
}

void User::SetUserName(QString name){
    this->UserName = name;
}

///
/// \brief User::SetFriendInfo
/// \param id
/// \param name
///
void User::SetFriendInfo(QString id ,QString name){
    // FRIEND *friends = new FRIEND();
    // qDebug()<<"new了一个friend";
    // friends->FriendName = name;
    // qDebug()<<"添加了朋友名字:"<<friends->FriendName;
    // friends->FriendID = id;
    // qDebug()<<"添加了朋友id:"<<friends->FriendID;
    // this->FriendList.append(friends);
    //
    FRIEND friends;
    friends.FriendID = id;
    friends.FriendName = name;
    this->FriendList.push_back(friends);
    qDebug()<<"加入了list";
}

///
/// \brief User::SetFriendHPPath设置好友头像路径
/// \param id
/// \param path
///
void User::SetFriendHPPath(QString id,QString path){
    int fid=id.toInt();

}

QString User::GetUserID(){
    return this->UserID;
}

// QVector<User::FRIEND> User::GetFriendList(){
//     return this->FriendList;
// }

void User::test(){
    qDebug()<<"测试，显示朋友信息：";
    for(auto it=FriendList.begin();it != FriendList.end();it++){
        qDebug()<<"ID："<<it->FriendID<<"  名字："<<it->FriendName;
    }
}

bool User::FindFriend(QString id){
    for(auto it = this->FriendList.begin();it!=this->FriendList.end();it++){
        if(!it->FriendID.compare(id)){
            qDebug()<<"User::FindFriend "<<it->FriendID<<id;
            qDebug()<<"User::FindFriend  已有"<<id<<"好友";
            return true;
        }
    }
    return false;
}

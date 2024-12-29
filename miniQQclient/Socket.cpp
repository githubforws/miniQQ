#include "Socket.h"
#include <QDebug>
#include <QJsonParseError>
#include <QAbstractSocket>
#include <QMessageBox>
#include <QPushButton>

///
/// \brief Socket::Socket
/// 实例化socket对象
/// 连接至服务器
/// 绑定消息接收函数
///
Socket::Socket() {
    qDebug()<<"Socket构造";
    client = new QTcpSocket(this);
    client->connectToHost(QHostAddress(IP), PORT);//连接至服务器

    SetUser(user);

    connect(client,SIGNAL(readyRead()),this,SLOT(RecvMessageSlots()));//绑定消息接收函数

}

void Socket::displayError(QAbstractSocket::SocketError socketError){
    switch (socketError) {
    case QAbstractSocket::HostNotFoundError:
        qDebug()<<"Fortune Client,The host was not found. Please check the,host name and port settings.";
        break;
    case QAbstractSocket::ConnectionRefusedError:
        qDebug()<<"Fortune Client,The connection was refused by the peer. "
                    "Make sure the fortune server is running, "
                    "and check that the host name and port "
                    "settings are correct.";
        break;
    default:
        qDebug()<<"Fortune ClientThe following error occurred: %1."<<client->errorString();
    }
}

void Socket::test(){
    qDebug()<<"Socket::test";
}

///
/// \brief Socket::SetUser 连接user
/// \param user
///
void Socket::SetUser(User* user){
    this->user=user;
}


///
/// \brief Socket::~Socket
/// 断开连接
///
Socket::~Socket(){
    qDebug()<<"断开连接";
    client->disconnectFromHost();
    client->close();
}

///
/// \brief Socket::RecvMessageSlots
/// 接收来自服务器的所有消息并解析
/// 交由消息处理函数分析处理
///
void Socket::RecvMessageSlots(){
    QString buffer;
    Message msg;//存储消息

    buffer = client->readAll();//接收消息
    qDebug()<<"源消息："<<buffer;

    // QJsonParseError类用于在JSON解析期间报告错误。
    QJsonParseError jsonError;
    // 将json解析为UTF-8编码的json文档，并从中创建一个QJsonDocument。
    // 如果解析成功，返回QJsonDocument对象，否则返回null
    QJsonDocument doc = QJsonDocument::fromJson(buffer.toUtf8(), &jsonError);
    // 判断是否解析失败
    if (jsonError.error != QJsonParseError::NoError && !doc.isNull()) {
        qDebug() << "Json格式错误！" << jsonError.error;
        return;
    }

    QJsonObject rootObj = doc.object();//获取根

    QJsonValue codejs = rootObj.value("CODE");//获取操作码
    //qDebug()<<"codejs = "<<codejs<<"rootObj.value = "<<rootObj.value("CODE");
    QString tmp = codejs.toString();
    msg.CODE = tmp.toInt();
    QJsonValue fromwhojs = rootObj.value("fromwho");//获取来自谁
    msg.fromwho = fromwhojs.toString();
    QJsonValue towhojs = rootObj.value("towho");//获取发给谁
    msg.towho = towhojs.toString();
    QJsonValue timejs = rootObj.value("timeis");//获取发送时间
    msg.timeis = timejs.toString();
    QJsonValue passwdjs = rootObj.value("password");//获取密码
    msg.password = passwdjs.toString();
    QJsonValue contentjs = rootObj.value("content");//获取消息内容
    msg.content = contentjs.toString();

    qDebug()<<"解析后的消息："<<msg.CODE<<msg.fromwho<<msg.towho<<msg.timeis<<msg.password<<msg.content;

    //转换完毕后使用多线程方式交由消息处理函数处理
    MessageAnalysis(msg);
    buffer.clear();
}

///
/// \brief Socket::SendMessageSlots
/// \param message  构造好的消息
/// 向服务器发送消息
///
void Socket::SendMessageSlots(QString message){
    qDebug()<<"源消息："<<message.toUtf8().data()<<message.toUtf8().size();
    this->client->write(message.toUtf8().data());
    //this->client->write(message.toUtf8().data(),message.toUtf8().size());
}

void Socket::testSlots(){

}

///
/// \brief Socket::SetMessage
/// \param code 操作码
/// \param fromwho 消息发送者，一般为客户端本身
/// \param towho 消息接收者id
/// \param time 发送消息的时间
/// \param passwd 密码，只有少数验证的时候用（后期改掉
/// \param content 实际要发的消息内容
/// \return 返回构造好的消息
/// 构造消息
///
QString Socket::SetMessage(int code,QString fromwho,QString towho,QString time,QString passwd,QString content){
    QString buf;
    qDebug()<<"构造消息";
    buf = SetCode + QString::number(code) ;
    buf += SetFromwho + fromwho + SetTowho + towho + SetTime + time +SetPassword + passwd +SetContent + content + SetEnd;
    return buf;
}

///
/// \brief Socket::AgreeFriendRequestSlot 点击同意好友申请
///
void Socket::AgreeFriendRequestSlot(){
    qDebug()<<"点击了同意";
    this->SendMessageSlots(this->SetMessage(RETURNFRIENDREQUEST,user->GetUserID(),user->NewFriendRequestID,"","","1"));//发送同意申请
    user->NewFriendRequestID.clear();
}

///
/// \brief Socket::DisagreeFriendRequestSlot 点击了拒绝好友申请
///
void Socket::DisagreeFriendRequestSlot(){
    qDebug()<<"点击了拒绝";
    user->NewFriendRequestID.clear();
}

///
/// \brief Socket::MessageAnalysis 消息处理，根据操作码的不同向主函数发送不同的信号处理消息
/// \param msg 解析好的消息
///
void Socket::MessageAnalysis(Message msg){
    switch (msg.CODE) {
    case LOGINSUCCESFUL:{
        qDebug()<<"登录成功";
        emit LoginSuccesSignal();//发送登录成功信号，显示主界面
        qDebug()<<"发送登录成功信号";
        this->user->SetUserName(msg.content);
        break;
    }
    case LOGINERRORACCOUNTNUM:{
        qDebug()<<"登录失败，账号错误";
        emit LoginErrorAccountnumSignal();//发送登录失败信号，重新显示登录界面
        break;
    }
    case LOGINERRORPASSWD:{
        qDebug()<<"登录失败，密码错误";
        emit LoginErrorpasswdSignal();//发送登录失败信号，重新显示登录界面
        break;
    }
    case REGISTERSUCCESFUL:{
        qDebug()<<"注册成功";
        emit RegisterSuccesSignal();//注册成功信号，显示主界面
        user->SetUserinfo(msg.content,"");
        break;
    }
    case UPDATEFRIEND:{
        qDebug()<<"更新好友信息";
        QStringList list = msg.content.split("\n");//好友与好友之间以\n分割
        qDebug()<<"list："<<list;
        for(QString str:list){
            qDebug()<<"str："<<str;
            if(str.isEmpty())
                break;
            QStringList list2 = str.split('/');//好友id与好友昵称以/分割
            qDebug()<<"朋友信息："<<list2[0]<<list2[1];
            if(!this->user->FindFriend(list2[0]))
                this->user->SetFriendInfo(list2[0],list2[1]);//设置好友的id和name并加入好友列表
        }
        qDebug()<<"添加好友完毕";
        this->user->test();//打印朋友信息看看是否添加成功
        emit UpdateFriendInfoSignal();//更新好友信号，更新好友列表
        break;
    }
    case NEWFRIENDMESSAGE:{
        qDebug()<<"收到了来自好友"<<msg.fromwho<<"的一条新消息";
        //发两个信号，均由主函数接收，未读消息数信号由主函数转发到UserChatList处理
        //一个信号提示好友列表显示未读消息数
        emit NewMessageCountSignal(msg.fromwho);
        //一个信号在对应好友聊天界面显示消息内容
        emit ShowNewMessageSignal(msg.fromwho,msg.content);
        break;
    }
    case ADDFRIENDREQUEST:{
        qDebug()<<"来自"<<msg.fromwho<<"的好友请求";
        user->NewFriendRequestID = msg.fromwho;
        QString remsg = msg.fromwho + "请求添加您为好友";
        QMessageBox* msgBox = new QMessageBox(QMessageBox::Information,"好友请求",remsg);//参数 Icon icon, const QString &title, const QString &text,
        msgBox->setText("好友请求");
        msgBox->setModal(false);//设置为非模态

        QPushButton *yes = new QPushButton();
        QPushButton *no = new QPushButton();

        yes = msgBox->addButton("同意",QMessageBox::AcceptRole);//添加同意按钮和拒绝按钮
        no = msgBox->addButton("拒绝",QMessageBox::RejectRole);

        connect(yes,SIGNAL(clicked(bool)),this,SLOT(AgreeFriendRequestSlot()));//绑定点击同意槽函数
        connect(no,SIGNAL(clicked(bool)),this,SLOT(DisagreeFriendRequestSlot()));//绑定点击同意槽函数
        connect(msgBox,SIGNAL(destroyed(QObject*)),this,SLOT(DisagreeFriendRequestSlot()));//点击关闭窗口

        msgBox->show();
        msgBox->setAttribute(Qt::WA_DeleteOnClose); //关掉消息框后删除指针
        break;
    }
    default:
        qDebug()<<"default code："<<msg.CODE;
        break;
    }
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"
#include "InputMessageItem.h"

#include <QRegularExpression>
#include <QMessageBox>
#include <QPushButton>
//#include <iostream>
#include <QListWidgetItem>

///
/// \brief MainWindow::MainWindow
/// \param parent
/// 最开始的实例化位置，所有要提前设置的都在这里设置
/// 实例化登录界面
/// 显示登录界面
/// 连接各类信号
///
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->user = new User();//实例化用户类
    this->UserMenu = new UserMenuItem(this);//实例化用户菜单
    this->UserList = new UserChatListItem(ui->UserChatListItemwidget);//用户列表
    //this->UserChat = new UserChatItem(ui->UserChatItemwidget);//每个好友有单独的一个聊天窗//父类？？？

    this->LoginInterface = new Login();//实例化登录界面
    this->LoginInterface->show();//显示登录界面

    connect(this,SIGNAL(DefaultSignal(QListWidgetItem*)),this->UserList,SLOT(DefaultSlot(QListWidgetItem*)));//当接收到update信号时，选择第一个好友作为默认显示对象
    connect(this,SIGNAL(NewMessageCountSignal(QString)),this->UserList,SLOT(NewMessageCountSlot(QString)));//转发信号到好友列表，显示未读消息数

    connect(this->LoginInterface,SIGNAL(LonginRequest()),this,SLOT(Verify()));//绑定登录信号，当接收到来自Login类的登录信号时执行验证账号密码操作
    connect(this->LoginInterface,SIGNAL(RegisterInstantiate()),this,SLOT(ReceiveRgister()));//当接收到来自Login类的Register注册信号时接收Register对象

    connect(ui->InputMessageItemwidget,SIGNAL(InputMessageSignals()),this,SLOT(SetMessageSlot()));//当接收到发送按钮的信号，调用构造消息槽函数
    connect(ui->InputMessageItemwidget,SIGNAL(InputMessageSignals()),this,SLOT(ShowMeInputMessageSlot()));//同时将我的消息显示在聊天框中

    connect(ui->SearchUserwidget,SIGNAL(SearchUIDSignal(QString)),this,SLOT(SearchUIDSlotl(QString)));//添加好友信号
    connect(this->UserMenu,SIGNAL(GetUserInfoSignal()),this,SLOT(GetUserInfoSlot()));//显示用户信息信号
    connect(this,SIGNAL(UserInfoSignal(QString,QString,QString)),this->UserMenu,SLOT(ShowUserInfoSlot(QString,QString,QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

///
/// \brief MainWindow::Verify
/// 接收来自Login类的登录信息并进行验证
///
void MainWindow::Verify(){
    //获取输入的账号密码
    this->LoginAccountNumber = this->LoginInterface->GetAccountnumber();
    this->LoginPasswd = this->LoginInterface->GetPasswd();

    QString cout = "登录账号为：" + LoginAccountNumber + "  登录密码为：" + LoginPasswd;
    qDebug()<<cout;

    if(this->LoginAccountNumber.isEmpty() || this->LoginPasswd.isEmpty()){
        qDebug()<<"账号或密码为空返回";
        return;
    }

    this->LoginInterface->hide();//隐藏登录界面
    if(RegisterInterface!=NULL)
        this->RegisterInterface->hide();//如果有注册界面则隐藏注册界面
    qDebug()<<"隐藏登录和注册界面";

    if(client==nullptr)
        client = new Socket();//实例化聊天的SOCKET

    QString buf = this->client->SetMessage(LOGIN,LoginAccountNumber,"","",LoginPasswd,"");//构造登录信息
    qDebug()<<"构造登录消息："<<buf;

    client->SendMessageSlots(buf);//发送账号信息进行验证

    if(!connected)
        ConnectClient();//连接client的信号
    //经过验证后的账号密码保存到User类
    //this->show();//验证成功显示主界面
    //验证失败显示登录界面
    //init();//显示主界面并加载好友信息
}

///
/// \brief MainWindow::ReceiveRgister
///接收来自Login类的信号，并接受Register对象
///
void MainWindow::ReceiveRgister(){
    this->RegisterInterface = this->LoginInterface->GetRegister();//接收Register对象
    qDebug()<<"收到了来自Login界面的信号,并接受了Register对象";
    connect(this->RegisterInterface,SIGNAL(RegisterRequest()),this,SLOT(RegisterRequestSlots()));//当接受到来自Register类的注册信号时执行验证操作
}

///
/// \brief MainWindow::RegisterRequestSlots
///接收来自Register类的注册信息并进行验证
///
void MainWindow::RegisterRequestSlots(){
    //获取昵称，密码
    this->RegisterName = this->RegisterInterface->GetName();
    this->RegisterPasswd = this->RegisterInterface->GetPasswd();

    QString cout = "`注册昵称为：" + RegisterName + "  注册密码为：" + RegisterPasswd;
    qDebug()<<cout;

    if(RegisterName.isEmpty() || RegisterPasswd.isEmpty()){
        qDebug()<<"账号或密码为空返回";
        return;
    }
    if(this->LoginInterface)
        this->LoginInterface->hide();//隐藏登录界面
    this->RegisterInterface->hide();//有注册界面则隐藏注册界面

    if(client==nullptr)
        client = new Socket();//实例化聊天的SOCKET

    QString buf = this->client->SetMessage(REGIST,"","","",RegisterPasswd,RegisterName);//构造注册信息
    qDebug()<<"构造注册信息"<<buf;

    client->SendMessageSlots(buf);//发送注册信息进行注册

    if(!connected)
        ConnectClient();//连接client的信号

    //经过注册后的信息保存到User类中
    //注册成功显示主界面
    //失败返回登录界面（暂时不会失败，可以先不写）
}

///
/// \brief MainWindow::SetMessageSlot 获取输入框的消息内容并进行构造消息
///
void MainWindow::SetMessageSlot(){
    qDebug()<<"调用了消息构造槽函数";
    QString inputmsg = ui->InputMessageItemwidget->GetInputMsg();//获得输入框的消息内容
    client->SendMessageSlots(client->SetMessage(SENDMSG,user->GetUserID(),this->UserList->GetUID(),"8:00","",inputmsg));
}

///
/// \brief MainWindow::ShowMeInputMessageSlot 显示“我”发出的气泡信息内容
///
void MainWindow::ShowMeInputMessageSlot(){
    qDebug()<<"显示我发送的消息内容";
    QString time;
    //dealMessageTime(time);//显示消息时间，有bug，会导致程序崩溃
    ChatMessage* messageW = new ChatMessage(ui->UserChatItemwidget->GetQListWidget());//取得
    QListWidgetItem* item = new QListWidgetItem(this->UserList->GetCurrentDisplayWindow());

    dealMessage(messageW, item,ui->InputMessageItemwidget->GetInputMsg() , time, ChatMessage::User_Me);
}

///
/// \brief MainWindow::dealMessageTime 显示系统时间
/// \param curMsgTime 系统时间
///
void MainWindow::dealMessageTime(QString curMsgTime)
{
    bool isShowTime = false;//是否展示时间

    qDebug()<<"进入dealMessageTime，curMsgTime="<<curMsgTime;

    //当消息数量>0时才考虑是否展示时间 第一条消息必须展示时间
    qDebug()<<"ui->listWidget->count() = "<<ui->UserChatItemwidget->GetCount();

    if(ui->UserChatItemwidget->GetCount() > 0) {
        QListWidgetItem* lastItem = ui->UserChatItemwidget->GetItem();//第几列

        ChatMessage* messageW = (ChatMessage*)ui->UserChatItemwidget->GetItemWidget(lastItem);//

        int lastTime = messageW->time().toInt();//获取上一条消息的时间
        int curTime = curMsgTime.toInt();//现在的时间

        qDebug() << "lastTime = " <<lastTime<<"  curTime = "<<curTime<<"  curTime - lastTime = "<<curTime - lastTime;

        isShowTime = ((curTime - lastTime) > 60); // 两个消息相差一分钟则展示时间
        //        isShowTime = true;
    } else {
        //第一条消息 必须展示时间
        isShowTime = true;
    }

    //如果需要展示时间
    qDebug()<<"isShowTime = "<<isShowTime;

    if(isShowTime) {
        ChatMessage* messageTime = new ChatMessage(ui->UserChatItemwidget->GetQListWidget());
        //ChatMessage* messageTime = new ChatMessage(ui->UserChatItemwidget->GetparentWidget());
        QListWidgetItem* itemTime = new QListWidgetItem(ui->UserChatItemwidget->GetQListWidget());

        QSize size = QSize(this->width(), 40);

        qDebug()<<"size="<<size;

        messageTime->resize(size);
        itemTime->setSizeHint(size);

        qDebug()<<"curMsgTime="<<curMsgTime<<"  size="<<size<<"  ChatMessage::User_Time="<<ChatMessage::User_Time;

        messageTime->setText(curMsgTime, curMsgTime, size, ChatMessage::User_Time);
        //ui->UserChatItemwidget->GetQListWidget()->setItemWidget(itemTime, messageTime);
        this->UserList->GetCurrentDisplayWindow()->setItemWidget(itemTime, messageTime);//在当前窗口上绘制时间
        qDebug()<<"ui->listWidget->setItemWidget";

    }

}

///
/// \brief MainWindow::dealMessage
/// \param messageW
/// \param item
/// \param text
/// \param time
/// \param type
///
void MainWindow::dealMessage(ChatMessage *messageW, QListWidgetItem *item, QString text, QString time,  ChatMessage::User_Type type)
{
    qDebug()<<"进入dealMessage";

    qDebug()<<"当前聊天框宽 = "<<this->UserList->GetCurrentDisplayWindow()->width();

    messageW->setFixedWidth(this->UserList->GetCurrentDisplayWindow()->width());

    QSize size = messageW->fontRect(text);//窗口尺寸

    qDebug()<<"messageW size="<<size<<"   真实窗口尺寸="<<this->UserList->GetCurrentDisplayWindow()->width();

    item->setSizeHint(size);
    messageW->setText(text, time, size, type);

    this->UserList->GetCurrentDisplayWindow()->setItemWidget(item, messageW);//在当前窗口上绘制本客户端发送的消息内容
    qDebug()<<"MainWindow::dealMessage 绘制消息结束";
}

///
/// \brief MainWindow::ShowMainSlot 显示主界面槽函数
///
void MainWindow::ShowMainSlot(){
    this->user->SetUserinfo(LoginAccountNumber,LoginPasswd);
    this->client->SetUser(user);//连接user到socket
    qDebug()<<"显示主界面";
    this->show();
    qDebug()<<"MainWindow::ShowMainSlot()emit test";
    //connect(this,SIGNAL(test()),this->UserMenu,SLOT(on_pushButton_clicked()));
    //connect(this,SIGNAL(test()),this->UserMenu,SLOT(test()));
    //connect(this,SIGNAL(test()),this->client,SLOT(test()));

    //emit test();
}

void MainWindow::GetUserInfoSlot(){
    emit UserInfoSignal(this->user->GetUserID(),this->user->GetUserName(),this->user->GetPasswd());
}


///
/// \brief MainWindow::LoginErrorAccountnumSlot登录账号错误槽函数
///
void MainWindow::LoginErrorAccountnumSlot(){
    qDebug()<<"登录账号错误槽函数";
    this->LoginInterface->show();//显示登录界面
    QMessageBox().information(NULL,"error","账号不存在");
}

///
/// \brief MainWindow::LoginErrorPasswdSlot 登录密码错误槽函数
///
void MainWindow::LoginErrorPasswdSlot(){
    qDebug()<<"登录密码错误槽函数";
    this->LoginInterface->show();//显示登录界面
    QMessageBox().information(NULL,"error","密码不正确");
}

void MainWindow::UpdateUserListSlot(){
    for(auto it=this->user->FriendList.begin();it != this->user->FriendList.end();it++){
        qDebug()<<"更新显示好友名片";
        //qDebug()<<ui->UserChatListItemwidget;
        if(this->UserList->Exist(it->FriendID))
            continue;

        QListWidgetItem* item = this->UserList->AddWidgetMsgItem(it->FriendID,it->FriendName);//添加一张好友名片

        qDebug()<<"给"<<it->FriendID<<it->FriendName<<"分配了一个聊天窗口,并绑定";
        UserChatItem* newUserChat = new UserChatItem(ui->UserChatItemwidget);//为每个好友分配一个聊天窗口

        this->UserList->SetUserChat(it->FriendID,newUserChat);//绑定好友id与聊天窗口

        if(it==this->user->FriendList.begin()){
            //默认选中第一个好友
            qDebug()<<"默认选中第一个好友,发送了一个默认信号";
            emit DefaultSignal(item);
        }
    }
}

void MainWindow::NewMessageCountSlot(QString id){
    qDebug()<<"主函数收到新消息信号，并进行转发"<<id;
    emit NewMessageCountSignal(id);
}

void MainWindow::ShowNewMessageSlot(QString id,QString newmsg){
    qDebug()<<"主函数收到新消息信号，并进行显示"<<id<<newmsg;
    QString time;
    bool flag=false;
    if(this->UserList->GetUID().compare(id)){
        this->UserList->DrawUnreadMessages(id);//当要绘制消息的窗口与目前的窗口不是同一个窗口时显示要绘制的界面并置于后台绘制
        flag=true;
        qDebug()<<"在后台绘制未读消息";
    }
    ChatMessage* messageW = new ChatMessage(ui->UserChatItemwidget->GetQListWidget());//在对应id的聊天界面中显示消息
    QListWidgetItem* item = new QListWidgetItem(this->UserList->GetUserChatItemQListWidget(id));//取得id对应的qlistwidget
    dealMessage(messageW,item,newmsg,time,ChatMessage::User_She);
    if(flag){
        this->UserList->DrawUnreadMessagesEnd(id);//绘制完未读消息后隐藏窗口
        qDebug()<<"在后台绘制未读消息结束";
    }
}


void MainWindow::SearchUIDSlotl(QString id){
    //构造添加好友信息并发送
    qDebug()<<"发送添加好友信息";
    client->SendMessageSlots(client->SetMessage(ADDFRIENDREQUEST,user->GetUserID(),id,"","",""));
    QString msg = "已向" + id + "发送好友请求";
    QMessageBox* msgBox = new QMessageBox(QMessageBox::Warning,"",msg);//参数 Icon icon, const QString &title, const QString &text,
    msgBox->setModal(false);//设置为非模态
    msgBox->setAttribute(Qt::WA_DeleteOnClose); //关掉消息框后删除指针
    msgBox->show();
}

///
/// \brief MainWindow::ConnectClient 在实例化client后连接各个信号与槽函数
///
void MainWindow::ConnectClient(){
    connected = true;

    connect(this->client,SIGNAL(LoginSuccesSignal()),this,SLOT(ShowMainSlot()));//登录成功，显示主界面
    connect(this->client,SIGNAL(LoginErrorAccountnumSignal()),this,SLOT(LoginErrorAccountnumSlot()));//登录失败，账号错误，显示登录界面
    connect(this->client,SIGNAL(LoginErrorpasswdSignal()),this,SLOT(LoginErrorPasswdSlot()));//登录失败，密码错误，显示登录界面
    connect(this->client,SIGNAL(RegisterSuccesSignal()),this,SLOT(ShowMainSlot()));//注册成功，显示主界面
    connect(this->client,SIGNAL(UpdateFriendInfoSignal()),this,SLOT(UpdateUserListSlot()));//更新好友列表
    connect(this->client,SIGNAL(NewMessageCountSignal(QString)),this,SLOT(NewMessageCountSlot(QString)));//转发--来自好友的一条新消息，更新消息提示数
    connect(this->client,SIGNAL(ShowNewMessageSignal(QString,QString)),this,SLOT(ShowNewMessageSlot(QString,QString)));//显示好友的新消息
}

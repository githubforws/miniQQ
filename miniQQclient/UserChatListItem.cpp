#include "userchatlistitem.h"
#include "ui_UserChatListItem.h"

UserChatListItem::UserChatListItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserChatListItem)
{
    ui->setupUi(this);

}

UserChatListItem::~UserChatListItem()
{
    delete ui;
}

///
/// \brief UserChatListItem::Exist 判断map中是否已绑定过id
/// \param id
/// \return
///
bool UserChatListItem::Exist(QString id){
    if(this->UserChatMap.contains(id))
        return true;
    return false;
}


///
/// \brief UserChatListItem::DefaultSlot
///
void UserChatListItem::DefaultSlot(QListWidgetItem* item){
    qDebug()<<"收到一个默认选中信号，发送一个选中该好友的信号";
    emit on_listWidgetClicked(item);
}

///
/// \brief UserChatListItem::SetUserChat 绑定好友id与聊天窗口
/// \param uuid 好友id
/// \param newUserChat 聊天窗口
///
void UserChatListItem::SetUserChat(QString uuid,UserChatItem *newUserChat){
    this->UserChatMap.insert(uuid,newUserChat);
}

///
/// \brief UserChatListItem::AddWidgetMsgItem 添加一个好友卡片
///
void UserChatListItem::AddWidgetMsgItem()
{
    auto pMsgItem = new MsgItem();//好友信息卡片
    QListWidgetItem *item = new QListWidgetItem;
    //item->setSizeHint( QSize(360, 70));
    item->setSizeHint( QSize(150, 70));//卡片大小
    pMsgItem->setCount(0);//未读消息数量
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, pMsgItem);

    connect(pMsgItem, &MsgItem::signal_selected, this, &UserChatListItem::slot_selected);//选中方式
    connect(pMsgItem, &MsgItem::signal_delete, this, &UserChatListItem::slot_delete);//删除好友，暂时没做
}

///
/// \brief UserChatListItem::AddWidgetMsgItem
///
void UserChatListItem::AddWidgetMsgItem(QString name)
{
    auto pMsgItem = new MsgItem();//好友信息卡片
    QListWidgetItem *item = new QListWidgetItem;
    //item->setSizeHint( QSize(360, 70));
    item->setSizeHint( QSize(150, 70));//卡片大小
    pMsgItem->setCount(0);//未读消息数量
    pMsgItem->setName(name);//设置好友名
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, pMsgItem);

    connect(pMsgItem, &MsgItem::signal_selected, this, &UserChatListItem::slot_selected);//选中方式
    connect(pMsgItem, &MsgItem::signal_delete, this, &UserChatListItem::slot_delete);//删除好友，暂时没做
}

QListWidgetItem* UserChatListItem::AddWidgetMsgItem(QString uuid,QString name)
{
    auto pMsgItem = new MsgItem();//好友信息卡片
    QListWidgetItem *item = new QListWidgetItem;
    //item->setSizeHint( QSize(360, 70));
    item->setSizeHint( QSize(160, 70));//卡片大小

    pMsgItem->setCount(0);//未读消息数量
    pMsgItem->setName(name);//设置好友名
    pMsgItem->setUuid(uuid);//设置好友id
    ui->listWidget->addItem(item);
    ui->listWidget->setItemWidget(item, pMsgItem);
    this->UidMsgitem.insert(uuid,pMsgItem);//保存uuid对应的msgitem

    connect(pMsgItem, &MsgItem::signal_selected, this, &UserChatListItem::slot_selected);//选中方式
    connect(pMsgItem, &MsgItem::signal_delete, this, &UserChatListItem::slot_delete);//删除好友，暂时没做

    return item;
}


///
/// 第一种选中的实现方式，点击选中好友卡片
///
void UserChatListItem::slot_selected(MsgItem *pWidget)
{
    qDebug()<<"选中了："<<pWidget;
    if(Q_NULLPTR == pWidget)
    {
        qDebug()<<"Q_NULLPTR == pWidget,11退出";
        return;
    }
    if(Q_NULLPTR != m_pCurrentItem)
    {
        qDebug()<<"Q_NULLPTR == m_pCurrentItem,12退出";
        m_pCurrentItem->selected(false);
    }

    pWidget->selected(true);
    m_pCurrentItem = pWidget;


    QString uid = pWidget->uuid();//取得当前选中的好友的id
    this->CurrentUID = uid;
    this->UserChatMap.value(uid)->show();//根据id找到对应的聊天界面并显示
    this->UserChatMap.value(uid)->raise();//显示在最顶层
    CurrentDisplayWindow = this->UserChatMap.value(uid);
    qDebug()<<"选中的好友ID："<<uid<<"展示了他的聊天窗口,并隐藏了其他窗口";
    for(auto it = this->UserChatMap.begin();it!=this->UserChatMap.end();it++){
        if(it.key()==uid)
            continue;
        if(!it.value()->isHidden())
            it.value()->hide();//没有被隐藏则隐藏
        qDebug()<<it.key()<<"被隐藏了";
    }
    pWidget->CountnumZero();//清空未读消息数
}

///
/// \brief UserChatListItem::DrawUnreadMessages 绘制未读消息前先显示界面
/// \param id
///
void UserChatListItem::DrawUnreadMessages(QString id){
    qDebug()<<"将"<<id<<"显示出来";
    LastID = GetUID();//本来显示的窗口的id
    Last_m_pCurrentItem = m_pCurrentItem;
    LastCurrentDisplayWindow = CurrentDisplayWindow;


    MsgItem *pWidget = this->UidMsgitem.value(id);
    qDebug()<<"在后台绘制未读消息："<<pWidget;
    if(Q_NULLPTR == pWidget)
    {
        qDebug()<<"Q_NULLPTR == pWidget,11退出";
        return;
    }
    if(Q_NULLPTR != m_pCurrentItem)
    {
        qDebug()<<"Q_NULLPTR == m_pCurrentItem,12退出";
        m_pCurrentItem->selected(false);
    }

    m_pCurrentItem = pWidget;

    this->UserChatMap.value(id)->show();//根据id找到对应的聊天界面并显示
    CurrentDisplayWindow = this->UserChatMap.value(id);

    this->UserChatMap.value(id)->lower();//显示在最底层
}

///
/// \brief UserChatListItem::DrawUnreadMessagesEnd绘制结束隐藏界面
/// \param id
///
void UserChatListItem::DrawUnreadMessagesEnd(QString id){
    this->UserChatMap.value(id)->hide();
    m_pCurrentItem = Last_m_pCurrentItem;
    CurrentDisplayWindow = LastCurrentDisplayWindow;

    qDebug()<<"将"<<id<<"隐藏下去，还原状态";
}

///
/// 第二种选中的实现方式,默认选中第一个好友
///
void UserChatListItem::on_listWidgetClicked(QListWidgetItem *pItem)
{
    qDebug()<<"收到一个默认选中好友信号";

    if (Q_NULLPTR == pItem)
    {
        qDebug()<<"Q_NULLPTR == pItem,1退出";
        return;
    }
    if (Q_NULLPTR == m_pCurrent)
    {
        m_pCurrent = pItem;
        auto item = dynamic_cast<MsgItem*>(ui->listWidget->itemWidget(pItem));

        QString uid = item->uuid();//取得当前选中的好友的id
        //item->CountnumZero();
        this->CurrentUID = uid;
        this->UserChatMap.value(uid)->show();//根据id找到对应的聊天界面并显示
        this->UserChatMap.value(uid)->raise();
        CurrentDisplayWindow = this->UserChatMap.value(uid);
        qDebug()<<"选中的好友ID："<<uid<<"展示了他的聊天窗口,并隐藏了其他窗口";
        for(auto it = this->UserChatMap.begin();it!=this->UserChatMap.end();it++){
            if(it.key()==uid)
                continue;
            if(!it.value()->isHidden())
                it.value()->hide();//没有被隐藏则隐藏
            qDebug()<<it.value()<<"被隐藏了";
        }

        if (Q_NULLPTR == item)
        {
            qDebug()<<"Q_NULLPTR == pItem,2退出";
            return;
        }
        item->selected(true);
        qDebug()<<"Q_NULLPTR == m_pCurrent,3退出";
        return;
    }
    auto item = dynamic_cast<MsgItem*>(ui->listWidget->itemWidget(m_pCurrent));

/*
    QString uid = item->uuid();//取得当前选中的好友的id
    this->UserChatMap.value(uid)->show();//根据id找到对应的聊天界面并显示
    qDebug()<<"选中的好友ID："<<uid<<"并展示了他的聊天窗口";
*/
    if (Q_NULLPTR == item)
    {
        return;
    }
    item->selected(false);
    m_pCurrent = pItem;
    item = dynamic_cast<MsgItem*>(ui->listWidget->itemWidget(pItem));
    if (item == Q_NULLPTR)
    {
        return;
    }
    item->selected(true);
}

///
/// \brief UserChatListItem::slot_delete 删除好友，暂时没做
/// \param pWidget
///
void UserChatListItem::slot_delete(QWidget* pWidget)
{
    delete pWidget;
    pWidget = Q_NULLPTR;
    QListWidgetItem *pItem = ui->listWidget->takeItem(ui->listWidget->currentRow());
    m_pCurrentItem = Q_NULLPTR;
    m_pCurrent = Q_NULLPTR;
}

QListWidget* UserChatListItem::GetCurrentDisplayWindow(){
    return this->CurrentDisplayWindow->GetQListWidget();
}

///
/// \brief UserChatListItem::on_btnAddClicked 点击添加好友，测试用
///
void UserChatListItem::on_btnAddClicked()
{
    AddWidgetMsgItem();
}

void UserChatListItem::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{

}

void UserChatListItem::NewMessageCountSlot(QString id){
    qDebug()<<"收到来自主界面转发过来的未读消息提醒，更新未读消息数";
    for(int i=0;i<(ui->listWidget->count());i++){
        auto pmsgitem = ui->listWidget->item(i);
        qDebug()<<"pmsgitem:"<<pmsgitem;
        auto item = dynamic_cast<MsgItem*>(pmsgitem->listWidget()->itemWidget(pmsgitem));
        qDebug()<<"id:"<<item->uuid();
        if(!item->uuid().compare(id)){
            item->setCountNum();
            qDebug()<<"未读消息数+1";
        }
    }
}

QListWidget* UserChatListItem::GetUserChatItemQListWidget(QString id){
    return this->UserChatMap.value(id)->GetQListWidget();
}


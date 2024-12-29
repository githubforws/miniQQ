#ifndef USERCHATLISTITEM_H
#define USERCHATLISTITEM_H

#include <QWidget>
#include <QListWidgetItem>
#include <QMouseEvent>
#include <QMap>
#include "MsgItem.h"
#include "UserChatItem.h"

namespace Ui {
class UserChatListItem;
}

class UserChatListItem : public QWidget
{
    Q_OBJECT

public:
    explicit UserChatListItem(QWidget *parent = nullptr);
    ~UserChatListItem();

private:
    Ui::UserChatListItem *ui;
    MsgItem* m_pCurrentItem{ Q_NULLPTR };
    MsgItem* Last_m_pCurrentItem{ Q_NULLPTR };
    QMap<QString,UserChatItem*> UserChatMap;//好友id与聊天界面绑定
    QMap<QString,MsgItem*> UidMsgitem;//uid对应的Msgitem
    QListWidgetItem* m_pCurrent{ Q_NULLPTR };
    UserChatItem* CurrentDisplayWindow;//当前显示的窗口
    UserChatItem* LastCurrentDisplayWindow;//上次显示的窗口
    QString CurrentUID;//当前显示的窗口所对应的好友id
    QString LastID;//最后一次显示界面的id

public:
    void AddWidgetMsgItem();//添加一个好友名片
    void AddWidgetMsgItem(QString name);//
    //void AddWidgetMsgItem(QString uuid,QString name);//
    QListWidgetItem* AddWidgetMsgItem(QString uuid,QString name);//
    void SetUserChat(QString uuid,UserChatItem *newUserChat);//绑定聊天窗口
    QListWidget* GetCurrentDisplayWindow();//取得当前显示的窗口
    QListWidget* GetUIDWindow(QString id);//取得指定好友的聊天窗口
    QString GetUID(){return CurrentUID;}//取得当前显示窗口的好友id
    QListWidget* GetUserChatItemQListWidget(QString id);//取得id对应的item对应的QListWidget
    void DrawUnreadMessages(QString);//将要绘制未读消息的界面显示在界面最底层并绘制消息，然后隐藏
    void DrawUnreadMessagesEnd(QString);//隐藏
    bool Exist(QString);//根据id判断map中是否已绑定过该id true有 false无


private slots:
    void slot_selected(MsgItem* pWidget);
    void slot_delete(QWidget *);
    void on_listWidgetClicked(QListWidgetItem* pItem);
    void on_btnAddClicked();

    void on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);

public slots:
    void DefaultSlot(QListWidgetItem*);//默认信号
    void NewMessageCountSlot(QString);//来自主界面转发的信号，更新好友未读消息数
};

#endif // USERCHATLISTITEM_H

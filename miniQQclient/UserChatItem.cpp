#include "UserChatItem.h"
#include "ui_UserChatItem.h"
#include <QPainter>

UserChatItem::UserChatItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::UserChatItem)
{
    ui->setupUi(this);

}

UserChatItem::~UserChatItem()
{
    delete ui;
}

int UserChatItem::GetCount(){
    return ui->listWidget->count();
}

QListWidgetItem* UserChatItem::GetItem(){
    return ui->listWidget->item(GetCount()-1);
}

QWidget* UserChatItem::GetItemWidget(QListWidgetItem* lastItem){
    return ui->listWidget->itemWidget(lastItem);
}

QWidget* UserChatItem::GetparentWidget(){
    return ui->listWidget->parentWidget();
}

QListWidget* UserChatItem::GetQListWidget(){
    return ui->listWidget;
}

QWidget* UserChatItem::GetQWidget(){

}

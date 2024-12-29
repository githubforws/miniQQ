#ifndef USERCHATITEM_H
#define USERCHATITEM_H

#include <QWidget>
#include <QListWidgetItem>

namespace Ui {
class UserChatItem;
}

class UserChatItem : public QWidget
{
    Q_OBJECT

public:
    explicit UserChatItem(QWidget *parent = nullptr);
    int GetCount();//返回listwidget的count值
    QListWidgetItem* GetItem();//返回item
    QWidget* GetItemWidget(QListWidgetItem* lastItem);
    QWidget* GetparentWidget();
    QListWidget* GetQListWidget();
    ~UserChatItem();
    QWidget* GetQWidget();//

private:
    Ui::UserChatItem *ui;
};

#endif // USERCHATITEM_H

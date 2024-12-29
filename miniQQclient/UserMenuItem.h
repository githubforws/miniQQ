#ifndef USERMENUITEM_H
#define USERMENUITEM_H
#include "UserInfoUI.h"

#include <QWidget>

namespace Ui {
class UserMenuItem;
}

class UserMenuItem : public QWidget
{
    Q_OBJECT

public:
    explicit UserMenuItem(QWidget *parent = nullptr);
    ~UserMenuItem();

public slots:
    void on_pushButton_clicked();
    void test();
    void ShowUserInfoSlot(QString,QString,QString);//接收用户信息

public slots:
    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

signals:
    void GetUserInfoSignal();//向主函数发送一个请求用户信息的信号
    void SetUserInfoSignal(QString,QString,QString);//向用户ui界面发送用户信息

private:
    Ui::UserMenuItem *ui;
    UserInfoUI* userinfoui;
};

#endif // USERMENUITEM_H

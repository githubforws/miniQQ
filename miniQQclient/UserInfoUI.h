#ifndef USERINFOUI_H
#define USERINFOUI_H


#include <QWidget>

namespace Ui {
class UserInfoUI;
}

class UserInfoUI : public QWidget
{
    Q_OBJECT

public:
    explicit UserInfoUI(QWidget *parent = nullptr);
    ~UserInfoUI();

private:
    Ui::UserInfoUI *ui;

public slots:
    void SetUserInfoSlot(QString,QString,QString);


};

#endif // USERINFOUI_H

#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>

namespace Ui {
class Register;
}

class Register : public QWidget
{
    Q_OBJECT

public:
    explicit Register(QWidget *parent = nullptr);
    ~Register();

signals:
    void RegisterRequest();//点击注册按钮时向Login类发送信号，使其向MainWindow类发送信号

private:
#define INPUTMAXLENTH 20 //最大输入长度为20
#define INPUTMINLENTH 6 //最小输入长度为6
    Ui::Register *ui;
    QString NameR;
    QString PasswdR;
    QString PasswdReR;

public:
    void RegisterRequestSlot();//emit向登录界面发送一个实例化信号
    QString GetName();
    QString GetPasswd();

private slots:
    void on_RegisterpushButton_clicked();//接收按下立即注册按钮信号，并进行对应操作
};

#endif // REGISTER_H

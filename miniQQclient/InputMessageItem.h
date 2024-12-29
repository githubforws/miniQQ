#ifndef INPUTMESSAGEITEM_H
#define INPUTMESSAGEITEM_H

#include <QWidget>
#include "ChatMessage.h"

namespace Ui {
class InputMessageItem;
}

class InputMessageItem : public QWidget
{
    Q_OBJECT

public:
    explicit InputMessageItem(QWidget *parent = nullptr);
    ~InputMessageItem();
    QString GetInputMsg();//获取输入的内容

signals:
    void InputMessageSignals();


private slots:
    void on_SendMessagepushButton_clicked();

    void on_FilepushButton_clicked();

private:
    Ui::InputMessageItem *ui;
    QString InputMsg;//文本框中输入的内容
};

#endif // INPUTMESSAGEITEM_H

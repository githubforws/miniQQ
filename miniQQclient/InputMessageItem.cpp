#include "InputMessageItem.h"
#include "ui_InputMessageItem.h"

#include <QDebug>

InputMessageItem::InputMessageItem(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::InputMessageItem)
{
    ui->setupUi(this);
    // ui->SendMessagepushButton->setFocus();
    // ui->SendMessagepushButton->setDefault(1);
    // connect(ui->SendMessagepushButton,SIGNAL(returnPressed()),ui->SendMessagepushButton,SLOT(on_SendMessagepushButton_clicked()));
}

InputMessageItem::~InputMessageItem()
{
    delete ui;
}

void InputMessageItem::on_SendMessagepushButton_clicked()
{
    QString time;//获取时间，后面要建立一个时间类专门管理时间

    InputMsg = ui->InputMessagetextEdit->toPlainText();
    qDebug()<<"输入的内容为1："<<InputMsg;
    if(InputMsg.isEmpty())
        return;
    qDebug()<<"发送了InputMessageSignals信号";
    emit InputMessageSignals();

    ui->InputMessagetextEdit->clear();//清空输入框
}

QString InputMessageItem::GetInputMsg(){
    return this->InputMsg;
}


void InputMessageItem::on_FilepushButton_clicked()
{
    qDebug()<<"点击了文件按钮";
}


#include "SearchUser.h"
#include "ui_SearchUser.h"

SearchUser::SearchUser(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::SearchUser)
{
    ui->setupUi(this);
}

SearchUser::~SearchUser()
{
    delete ui;
}

void SearchUser::on_SearchpushButton_clicked()
{
    this->SearchUID = ui->InputUserIdlineEdit->text().trimmed();
    emit SearchUIDSignal(SearchUID);
}


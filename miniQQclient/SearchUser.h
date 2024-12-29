#ifndef SEARCHUSER_H
#define SEARCHUSER_H

#include <QWidget>

namespace Ui {
class SearchUser;
}

class SearchUser : public QWidget
{
    Q_OBJECT

public:
    explicit SearchUser(QWidget *parent = nullptr);
    ~SearchUser();

private slots:
    void on_SearchpushButton_clicked();

private:
    Ui::SearchUser *ui;
    QString SearchUID;

signals:
    void SearchUIDSignal(QString);
};

#endif // SEARCHUSER_H

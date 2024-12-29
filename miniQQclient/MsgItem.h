#ifndef MSGITEM_H
#define MSGITEM_H

#include <QWidget>

namespace Ui {
class MsgItem;
}

class MsgItem : public QWidget
{
    Q_OBJECT
    //可按照下面的方法自己添加需要的功能
    Q_PROPERTY(QString msg READ msg WRITE setMsg DESIGNABLE true)
    Q_PROPERTY(QString header READ header WRITE setHeader DESIGNABLE true)
    Q_PROPERTY(QString name READ name WRITE setName DESIGNABLE true)
    Q_PROPERTY(QString uuid READ uuid WRITE setUuid DESIGNABLE true)
    Q_PROPERTY(QString datetime READ datetime WRITE setDatetime DESIGNABLE true)
    Q_PROPERTY(int count READ count WRITE setCount DESIGNABLE true)

public:
    explicit MsgItem(QWidget *parent = nullptr);
    ~MsgItem();
    QString msg() const;
    void setMsg(const QString& msg);

    QString header() const;
    void setHeader(const QString& header);

    QString uuid() const
    {
        return m_uuid;
    }
    void setUuid(const QString& uuid)
    {
        m_uuid = uuid;
    }

    QString name() const;
    void setName(const QString& name);

    QString datetime() const;
    void setDatetime(const QString& datetime);

    int countnum=0;
    int count() const;
    void setCount(const int count);
    void setCount();
    void setCountNum(){this->countnum++;setCount();}
    void CountnumZero(){countnum = 0;}

    void setData( const QString &msg,
                 const QString& nick,
                 const QString& header,
                 const QString& name,
                 const QString& time );

    void selected(bool selected);

protected:
    virtual void mousePressEvent( QMouseEvent *event );


private slots:
    void on_btnDeleteClicked();

signals:
    void signal_selected(MsgItem*);
    void signal_delete(QWidget*);

private:
    Ui::MsgItem *ui;
    QString m_header;
    QString m_uuid;

};

#endif // MSGITEM_H

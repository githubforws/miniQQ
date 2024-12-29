#include "ChatMessage.h"
#include <QFontMetrics>
#include <QPaintEvent>
#include <QDateTime>
#include <QPainter>
#include <QMovie>
#include <QLabel>
#include <QDebug>

ChatMessage::ChatMessage(QWidget *parent) : QWidget(parent) {
    QFont te_font = this->font();
    te_font.setFamily("MicrosoftYaHei");//字体
    te_font.setPointSize(12);//大小

    this->setFont(te_font);
    m_leftPixmap = QPixmap(":/icon/defaultheadpicture.jpg");//左用户头像
    m_rightPixmap = QPixmap(":/icon/defaultheadpicture.jpg");//右用户头像

    m_loadingMovie = new QMovie(this);//播放器（不带声音，可做背景用）
    //m_loadingMovie->setFileName(":/img/loading4.gif");//播放转圈圈的gif

    m_loading = new QLabel(this);//对label的一些设置
    m_loading->setMovie(m_loadingMovie);
    m_loading->resize(16,16);
    m_loading->setAttribute(Qt::WA_TranslucentBackground , true);
    m_loading->setAutoFillBackground(false);

}


void ChatMessage::setText(QString text, QString time, QSize allSize, ChatMessage::User_Type userType)
{
    qDebug()<<"ChatMessage::setText";
    qDebug()<<"text="<<text<<"  userType="<<userType<<"  time="<<time;

    m_msg = text;//文本内容
    m_userType = userType;//是谁
    m_time = time;//时间戳
    //QDateTime::fromTime_t(time.toInt()).toString("hh:mm");
    m_curTime = QDateTime::fromMSecsSinceEpoch(time.toInt()).toString("hh:mm");//应该是将时间转为hh:mm格式

    qDebug()<<"m_curTime="<<m_curTime;

    m_allSize = allSize;

    qDebug()<<"m_allSize="<<m_allSize;

    /*
    if(userType == User_Me) {
        //如果是右用户
        qDebug()<<"走User_Me";
        if(!m_isSending) {
            m_loading->move(m_kuangRightRect.x() - m_loading->width() - 10, m_kuangRightRect.y()+m_kuangRightRect.height()/2- m_loading->height()/2);
            m_loading->show();
            m_loadingMovie->start();
        }
    }else if(userType == User_She){

    }
    else {
        qDebug()<<"走else";
        //左用户
        if(m_loading!=nullptr)
            m_loading->hide();

        qDebug()<<"走else结束";
    }
*/

    //更新显示
    qDebug()<<"this->update()";
    this->update();
}


QSize ChatMessage::fontRect(QString str)
{
    m_msg = str;
    int minHei = 50;
    int iconWH = 40;//头像大小
    int iconSpaceW = 20;//相对于当前widget  头像起始x
    int iconRectW = 5;
    int iconTMPH = 10;//头像起始y
    int sanJiaoW = 6;
    int kuangTMP = 20;
    int textSpaceRect = 12;//文本距框边距
    qDebug()<<"this->parentWidget()的类型是："<<this->parentWidget();

    m_kuangWidth = this->parentWidget()->width() - kuangTMP - 2*(iconWH+iconSpaceW+iconRectW);//除去三角形的和两边头像的宽度，其余的都是文字框的宽度
    m_textWidth = m_kuangWidth - 2*textSpaceRect;//文字内容的长度
    m_spaceWid = (this->parentWidget()->width() - m_textWidth)/2;//空白的宽度
    m_iconLeftRect = QRect(iconSpaceW, iconTMPH, iconWH, iconWH);//左头像的坐标
    m_iconRightRect = QRect(this->parentWidget()->width() - iconSpaceW - iconWH, iconTMPH, iconWH, iconWH);//右头像的坐标
    qDebug()<<"ChatMessage::fontRect "<<"m_kuangWidth"<<m_kuangWidth<<"  m_textWidth"<<m_textWidth<<"  m_spaceWid"<<m_spaceWid<<" m_iconLeftRect "<<m_iconLeftRect<<" m_iconRightRect"<<m_iconRightRect;

    QSize size = getRealString(m_msg); // 整个的size

    qDebug() << "fontRect Size:" << size;
    int hei = size.height() < minHei ? minHei : size.height();
    qDebug()<<"size.height() = "<<size.height()<<"  hei="<<hei << "  size.width()="<<size.width();

    m_sanjiaoLeftRect = QRect(iconWH+iconSpaceW+iconRectW, m_lineHeight/2, sanJiaoW, hei - m_lineHeight);
    //m_sanjiaoRightRect = QRect(this->width() - iconRectW - iconWH - iconSpaceW - sanJiaoW, m_lineHeight/2, sanJiaoW, hei - m_lineHeight);
    m_sanjiaoRightRect = QRect(this->parentWidget()->width() - iconRectW - iconWH - iconSpaceW - sanJiaoW, m_lineHeight/2, sanJiaoW, hei - m_lineHeight);

    if(size.width() < (m_textWidth+m_spaceWid)) {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), m_lineHeight/4*3, size.width()-m_spaceWid+2*textSpaceRect, hei-m_lineHeight);
        m_kuangRightRect.setRect(this->parentWidget()->width() - size.width() + m_spaceWid - 2*textSpaceRect - iconWH - iconSpaceW - iconRectW - sanJiaoW,
                                 m_lineHeight/4*3, size.width()-m_spaceWid+2*textSpaceRect, hei-m_lineHeight);
        // m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), m_lineHeight/4*3, size.width()-m_spaceWid+2*textSpaceRect, hei-m_lineHeight);
        // m_kuangRightRect.setRect(this->width() - size.width() + m_spaceWid - 2*textSpaceRect - iconWH - iconSpaceW - iconRectW - sanJiaoW,
        //                          m_lineHeight/4*3, size.width()-m_spaceWid+2*textSpaceRect, hei-m_lineHeight);
    } else {
        m_kuangLeftRect.setRect(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), m_lineHeight/4*3, m_kuangWidth, hei-m_lineHeight);
        m_kuangRightRect.setRect(iconWH + kuangTMP + iconSpaceW + iconRectW - sanJiaoW, m_lineHeight/4*3, m_kuangWidth, hei-m_lineHeight);
    }
    //文本框位置及大小
    m_textLeftRect.setRect(m_kuangLeftRect.x()+textSpaceRect,m_kuangLeftRect.y()+iconTMPH,
                           m_kuangLeftRect.width()-textSpaceRect,m_kuangLeftRect.height()-2*iconTMPH);
    m_textRightRect.setRect(m_kuangRightRect.x()+textSpaceRect,m_kuangRightRect.y()+iconTMPH,
                            m_kuangRightRect.width()-textSpaceRect,m_kuangRightRect.height()-2*iconTMPH+10);

    qDebug()<<"ChatMessage::fontRect   m_textLeftRect"<<m_textLeftRect<<"  m_textRightRect"<<m_textRightRect;
    return QSize(size.width(), hei);
}

///
/// \brief ChatMessage::getRealString
/// \param src
/// \return
/// 取得字符串的qsize
/// 对字符串长度进行判断以确定是否需要换行显示
///
QSize ChatMessage::getRealString(QString src)
{
    QFontMetricsF fm(this->font());//QFontMetricsF 类提供了关于字体的指标信息。它用于计算给定字体的字符和字符串的大小。
    //QFontMetricsF fm(this->parentWidget()->font());
    m_lineHeight = fm.lineSpacing();
    int nCount = src.count("\n");//换行次数
    int nMaxWidth = 0;//最大宽度
    if(nCount == 0) {
        //没有换行
        nMaxWidth = fm.horizontalAdvance(src);//字符的长度就是最大宽度
        qDebug()<<"ChatMessage::getRealString：nMaxWidth="<<nMaxWidth<<"  m_textWidth="<<m_textWidth<<"  m_lineHeight"<<m_lineHeight<<"  m_spaceWid"<<m_spaceWid;
        QString value = src;
        if(nMaxWidth > m_textWidth) {
            //如果字符总长度>文本框所能接受的最大字符长度
            //那么要对字符串分段换行
            nMaxWidth = m_textWidth;
            //int size = m_textWidth / fm.horizontalAdvance(src);//小数
            int num = fm.horizontalAdvance(src) / m_textWidth;//要换行的次数
            nCount += num;

        }
    } else {
        //如果存在换行
        QStringList list = src.split("\n");
        for(QString value:list){
            qDebug()<<"value = "<<value;
            nMaxWidth = fm.horizontalAdvance(value) > nMaxWidth ? fm.horizontalAdvance(value) : nMaxWidth;
            if(fm.horizontalAdvance(value) > m_textWidth) {
                nMaxWidth = m_textWidth;
                //int size = m_textWidth / fm.horizontalAdvance(value);
                int num = fm.horizontalAdvance(value) / m_textWidth;

                nCount += num;

            }
        }
    }
    return QSize(nMaxWidth+m_spaceWid, (nCount + 1) * m_lineHeight+2*m_lineHeight);
}

///
/// \brief ChatMessage::paintEvent
/// \param event
/// 重写paintEvent以绘制气泡框
///
void ChatMessage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);//消锯齿
    painter.setPen(Qt::NoPen);
    painter.setBrush(QBrush(Qt::gray));

    //qDebug()<<"绘制函数：m_msg = "<<m_msg;

    if(m_userType == User_Type::User_She) { // 用户
        //头像
        painter.drawPixmap(m_iconLeftRect, m_leftPixmap);

        //框加边
        QColor col_KuangB(234, 234, 234);
        painter.setBrush(QBrush(col_KuangB));
        painter.drawRoundedRect(m_kuangLeftRect.x()-1,m_kuangLeftRect.y()-1,m_kuangLeftRect.width()+2,m_kuangLeftRect.height()+2,4,4);
        //框
        QColor col_Kuang(255,255,255);
        painter.setBrush(QBrush(col_Kuang));
        painter.drawRoundedRect(m_kuangLeftRect,4,4);

        //三角
        QPointF points[3] = {
            QPointF(m_sanjiaoLeftRect.x(), 30),
            QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 25),
            QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 35),
        };
        QPen pen;
        pen.setColor(col_Kuang);
        painter.setPen(pen);
        painter.drawPolygon(points, 3);

        //三角加边
        QPen penSanJiaoBian;
        penSanJiaoBian.setColor(col_KuangB);
        painter.setPen(penSanJiaoBian);
        painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 24));
        painter.drawLine(QPointF(m_sanjiaoLeftRect.x() - 1, 30), QPointF(m_sanjiaoLeftRect.x()+m_sanjiaoLeftRect.width(), 36));

        //内容
        QPen penText;
        penText.setColor(QColor(51,51,51));
        painter.setPen(penText);
        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.setFont(this->font());
        painter.drawText(m_textLeftRect, m_msg,option);
    }  else if(m_userType == User_Type::User_Me) { // 自己
        //头像
        //        painter.drawRoundedRect(m_iconRightRect,m_iconRightRect.width(),m_iconRightRect.height());
        painter.drawPixmap(m_iconRightRect, m_rightPixmap);

        //框
        QColor col_Kuang(75,164,242);
        painter.setBrush(QBrush(col_Kuang));
        painter.drawRoundedRect(m_kuangRightRect,4,4);
        //qDebug()<<"m_kuangRightRect = "<<m_kuangRightRect;

        //三角
        QPointF points[3] = {
            QPointF(m_sanjiaoRightRect.x()+m_sanjiaoRightRect.width(), 30),
            QPointF(m_sanjiaoRightRect.x(), 25),
            QPointF(m_sanjiaoRightRect.x(), 35),
        };
        QPen pen;
        pen.setColor(col_Kuang);
        painter.setPen(pen);
        painter.drawPolygon(points, 3);

        //内容
        QPen penText;
        penText.setColor(Qt::white);
        painter.setPen(penText);
        QTextOption option(Qt::AlignLeft | Qt::AlignVCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        painter.setFont(this->font());
        painter.drawText(m_textRightRect,m_msg,option);
    }  else if(m_userType == User_Type::User_Time) { // 时间
        QPen penText;
        penText.setColor(QColor(153,153,153));
        painter.setPen(penText);
        QTextOption option(Qt::AlignCenter);
        option.setWrapMode(QTextOption::WrapAtWordBoundaryOrAnywhere);
        QFont te_font = this->font();
        te_font.setFamily("MicrosoftYaHei");
        te_font.setPointSize(10);
        painter.setFont(te_font);
        painter.drawText(this->rect(),m_curTime,option);
    }
}


#include "LAppWidget.h"
#include<QPainter>
#include<QRectF>
#include<QDebug>
#include<QTimer>

LAppWidget::LAppWidget(QWidget *parent) : QWidget(parent)
{

}

/*在指定的窗体区间绘制文本，让文本能够自适应窗体，而且随分辨率放大或者缩小*/
LDrawTextWidget::LDrawTextWidget(QWidget *parent) : QWidget(parent)
{
   m_rect = QRect(0,0,0,0);
   m_string = " ";
   m_pix = 400.0;
}

void LDrawTextWidget::paintEvent(QPaintEvent *)
{
    double width = this->width();
    double height = this->height();
    double size = qMin(width,height);
    QPainter painter(this);
    //painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width/ 2, height/ 2);
    painter.scale(size / 800.0, size / 800.0);
    painter.save();
    painter.setPen(Qt::green);
    m_rect = QRectF(-width/2,-height/2,width,height);
    double textwid = fontMetrics().width(m_string);
    QFont font;
    font.setPixelSize((width -textwid)*0.4);
    painter.setFont(font);
    painter.drawText(m_rect,Qt::AlignCenter, m_string);
    painter.restore();
}
void LDrawTextWidget::setStringText(QString string)
{
    m_string = string;
}

/*在指定的对话框区域绘制文本，让文本能够自适应窗体，而且随分辨率放大或者缩小*/
LDrawTextLabel::LDrawTextLabel(QWidget *parent) : QLabel(parent)
  ,m_timer(new QTimer(this))
  ,m_isflush(false)
{
   m_rect = QRect(0,0,0,0);
   m_string = " ";
   m_pix = 400.0;
   connect(m_timer,SIGNAL(timeout()),this,SLOT(SlotSecEvent()));
   m_timer->start(1000);
}

void LDrawTextLabel::SlotSecEvent()
{
    update();
    if(!m_isflush)
    {
        m_isflush = true;
    }
    else
    {
        m_isflush = false;
    }
}
void LDrawTextLabel::paintEvent(QPaintEvent *)
{
    double width = this->width();
    double height = this->height();
    double size = qMin(width,height);
    QPainter painter(this);
    //painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width/ 2, height/ 2);
    painter.scale(size / 200.0, size / 200.0);
    painter.save();
    if(m_isflush)
    {
        painter.fillRect(m_rect,Qt::red);
    }
    painter.setPen(Qt::cyan);
    m_rect = QRectF(-width/2,-height/2,width,height);
    double textwid = fontMetrics().width(m_string);
    QFont font;
    font.setPixelSize((width -textwid)*0.8);
    painter.setFont(font);
    painter.drawText(m_rect,Qt::AlignCenter, m_string);

    painter.restore();
}
void LDrawTextLabel::setStringText(QString string)
{
    m_string = string;
}

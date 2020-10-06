#include "LValueText.h"
#include<QTimer>
#include<QPainter>
#include<QRectF>
LValueText::LValueText(QWidget *parent) : QWidget(parent)
  ,m_timer(new QTimer(this))
  ,m_value(0)
  //,m_rectF(QRectF(0,0,0,0))
{

   connect(m_timer,SIGNAL(timeout()),this,SLOT(SlotSetValue()));
   m_timer->start(1000);
}

LValueText::~LValueText()
{
    if(m_timer)
    {
        delete m_timer;
        m_timer = NULL;
    }
}

void LValueText::setText(QString string)
{
    m_text = QString::number(m_value);
    string = m_text;
}
void LValueText::paintEvent(QPaintEvent *)
{
 QPainter painter(this);
 painter.setPen(Qt::red);
 QRectF rect = m_rectF;
  //m_rectF = QRectF(0,0,this->width(),this->height());
 painter.drawText(rect,m_text);


}


void LValueText::resizeEvent(QResizeEvent *)
{
    m_rectF = QRectF(0,0,this->width(),this->height());
}

void LValueText::SlotSetValue()
{
    m_value = qrand()%10+90;
    QString string="";
    setText(string);
    update();
}

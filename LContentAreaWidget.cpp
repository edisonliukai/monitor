#include "LContentAreaWidget.h"
#include"LMonitor.h"
#include"LAppCommom.h"
#include<QPainter>
#include<QPoint>
#include<QPen>
#include<QDebug>

// 内容区域的主界面显示 co2 spo2 spo2B ECG 的波形和参数
LContentAreaWidget::LContentAreaWidget(QWidget *parent) : QWidget(parent)
  ,m_layout(new QVBoxLayout)
{

  for(int i = 0;i<ITEM_NUM;++i)
  {
      m_waveChartArry[i] = NULL;
  }


  //InitWidget();
}

LContentAreaWidget::~LContentAreaWidget()
{
    if(!m_layout)
    {
        delete m_layout;
        m_layout =NULL;
    }
    for(int i = 0;i<ITEM_NUM;++i)
    {
        if(m_waveChartArry[i])
        {
            delete m_waveChartArry[i];
            m_waveChartArry[i] = NULL;
        }
    }
}

/*void LContentAreaWidget::paintEvent(QPaintEvent *)
{
    qDebug()<<"this is painterEvebt";
   /*QPainter painter(this);
   painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

   //m_waveChartArry[1]->startDrawWave();
   painter.save();
   QPen pen(Qt::DashLine);

   PARAMETER_ITEM spo2Item;
   InitItem(spo2Item);
   pen.setColor(spo2Item.m_color);
   painter.setPen(pen);
   painter.drawText(spo2Item.m_spo2Rect,"SPO2");
   painter.drawText(spo2Item.m_lRect,"89");
   painter.drawText(spo2Item.m_hRect,"100");
   painter.drawText(spo2Item.m_prRect,"PR  50");
   painter.drawText(spo2Item.m_piRect,"PI  5.0%");
   painter.drawText(spo2Item.m_spospmetRect,"SpMet 2.5%");
   QFont font;
   font.setPointSize(48);
   //font.setPixelSize(68);
   font.setFamily("Microsoft YaHei");
   painter.setFont(font);
   //painter.drawText(spo2Item.m_valueRect,"98");
   pen.setColor(Qt::red);
   painter.setPen(pen);
   painter.drawLine(0,this->height()/ITEM_NUM,this->width()*3/ITEM_NUM,this->height()/ITEM_NUM);
   pen.setColor(Qt::green);
   painter.setPen(pen);
   painter.drawLine(0,this->height()/ITEM_NUM*2,this->width()*3/ITEM_NUM,this->height()/ITEM_NUM*2);
   pen.setColor(Qt::yellow);
   painter.setPen(pen);
   painter.drawLine(0,this->height()/ITEM_NUM*3,this->width()*3/ITEM_NUM,this->height()/ITEM_NUM*3);

   painter.restore();
    //update();
}*/

void LContentAreaWidget::resizeEvent(QResizeEvent *)
{

    //qDebug()<<"m_rect.width = "<<this->height()/ITEM_NUM;
    //qDebug()<<"m_rect,height = "<<rect.height();
}

void LContentAreaWidget::InitItem(PARAMETER_ITEM&item)
{
     int width = this->width()/4;
     int height = this->height()/4;
    item.m_name = "spo2";
    item.m_color = Qt::cyan;
    item.m_isflash = false;
    QRect spo2 = QRect(width*3,0,40,20);
    QRect l = QRect(width*3,height/8*5,width/8,height/4);
    QRect h= QRect(width*3,height/8*7,width/6,height/4);
    QRect value= QRect(width*3+width/5,0,width/2,height);
    QRect pr = QRect(width*3+width/5*4,height/8*3,width/4,height/4);
    QRect pi = QRect(width*3+width/5*4,height/8*9/2,width/4,height/4);
    QRect spMet = QRect(width*3+width/5*4,height/8*6,width/4,height/4);
    item.m_spo2Rect = spo2;
    item.m_lRect = l;
    item.m_hRect = h;
    item.m_valueRect = value;
    item.m_prRect = pr;
    item.m_piRect = pi;
    item.m_spospmetRect =spMet;
}

void LContentAreaWidget::InitWidget()
{
   if(!m_layout)
   {
       return;
   }

   for(int i = 0;i<ITEM_NUM;++i)
   {
       m_waveChartArry[i] = new LSmoothWaveform;
       m_layout->addWidget(m_waveChartArry[i]);

       if(i ==  PHYSIOLOGICAL_OF_SPO2_A)
       {
         m_waveChartArry[i]->setPointColor(Qt::red);
       }
       else if(i == PHYSIOLOGICAL_OF_SPO2_B)
       {
         m_waveChartArry[i]->setPointColor(Qt::green);
       }
       else if(i == PHYSIOLOGICAL_OF_ECG)
       {
           m_waveChartArry[i]->setPointColor(Qt::yellow);
       }
       else if(i == PHYSIOLOGICAL_OF_CO2)
       {
           m_waveChartArry[i]->setPointColor(Qt::cyan);
       }

       m_waveChartArry[i]->startDrawWave();
   }
   m_layout->setContentsMargins(0,0,0,0);
   m_layout->setSpacing(0);
   this->setLayout(m_layout);
}



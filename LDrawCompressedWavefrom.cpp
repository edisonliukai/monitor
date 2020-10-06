#include "LDrawCompressedWavefrom.h"
#include "ui_LDrawCompressedWavefrom.h"

#include<QPainter>
#include<QDebug>
#include<QTimer>

CompressedWave::CompressedWave(QWidget *parent) :
    QWidget(parent)
  ,m_ifDrawWave(false)
  ,m_ifDrawGird(false)
  ,m_path(NULL)
  ,m_timer(new QTimer(this))
  ,m_num(0)
  ,m_dataLen(0)
{
    m_waveColor = QColor(Qt::cyan);
    //setPointData();
    //m_dataLen = this->width();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(SlotUpdate()));
    m_timer->start(1000);
}

CompressedWave::~CompressedWave()
{
   if(m_timer)
   {
       delete m_timer;
       m_timer =NULL;
   }
}

void CompressedWave::setDrawWaveDirection(DRAW_WAVE_DIRCTION  direction)
{
    m_drawWaveDirction =  direction;
}

void CompressedWave::ifStartDrawWave(bool flag)
{
    m_ifDrawWave = flag;
}

void CompressedWave::ifDrawGird(bool flag)
{
    m_ifDrawGird = flag;
}

void CompressedWave::SlotSetData()
{

   //setPointData();
}

void CompressedWave::SlotUpdate()
{
    update();
}
void CompressedWave::setPointData()
{
    double width = this->width();

    for(int i = 0;i< 45;++i)
    {
        int y = qrand()%60+40;
        int x = 0;

        if(m_drawWaveDirction == DRAW_WAVE_FROM_LEFT)
        {
            x = width/44*i;


        }
        else if(m_drawWaveDirction == DRAW_WAVE_FROM_RIGHT)
        {
            x = width-width/44*i;
        }
        QPoint p(x,y);
        m_pointList.push_back(p);


    }

    createQpainterPath();
}

void CompressedWave::setDataLen(int data)
{
        this->m_dataLen = data;
}

void CompressedWave::clearPointData()
{
    if(!m_pointList.empty())
    {
        m_pointList.clear();
    }
}

void CompressedWave::createQpainterPath()
{
   if(!m_path)
   {
       m_path = new QPainterPath;
   }

}

void CompressedWave::drawGird(QPainter &painter)
{

     painter.save();
     painter.setPen(Qt::white);

    int w =this->width();
    int h = this->height();
    QRect rect = QRect(10,10,w-10,h-10);
    //painter.drawRect(rect);
    for(int i = 0;i<this->width();++i)
    {
        for(int j=0;j<this->height();++j)
        {
            if(i%6 == 0||j%4==0)
            {

             painter.drawPoint(i*6,j*6);
            }
        }

    }
    painter.restore();
}
void CompressedWave::paintEvent(QPaintEvent *)
{


    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    QPen pen(Qt::white);
    pen.setWidth(1);

    painter.setPen(pen);
    if(m_ifDrawGird)
    {
        drawGird(painter);
        //m_ifDrawGird = false;
    }

    if(m_num == 0)
    {
        setPointData();
    }

    pen.setColor(m_waveColor);
    pen.setWidth(2);
    painter.setPen(pen);


    if(m_pointList.empty())
    {
       // qDebug()<<"m_pointList is empty";
        return;
    }
    if(m_num<=43 && m_ifDrawWave)
    {

        QPointF p1 = m_pointList.at(m_num);

        QPointF p2 = m_pointList.at(m_num+1);

        painter.drawLine(p1,p2);
        m_path->moveTo(p1);
        m_path->lineTo(p2);
        painter.drawPath(*m_path);
    }

    m_num++;
    if(m_num >=44)
    {
        m_num = 0;
        //m_ifDrawWave = false;
        if(!m_pointList.empty())
        {
            m_pointList.clear();
        }

        delete m_path;
        m_path = NULL;
        //m_pathList.push_back(m_path);
    }
    if(m_drawWaveDirction == DRAW_WAVE_FROM_RIGHT)
    {
        pen.setStyle(Qt::DashLine);
        pen.setWidth(1);
        painter.setPen(pen);
        painter.drawLine(0,this->height(),this->width(),this->height());
    }

}

void CompressedWave::resizeEvent(QResizeEvent *)
{
    //this->m_dataLen = this->width();
}

void CompressedWave::setWaveColor(QColor color)
{
    m_waveColor = color;
}

LDrawCompressedWavefrom::LDrawCompressedWavefrom(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LDrawCompressedWavefrom)
{
    ui->setupUi(this);
    //int value = ui->waveWdt->width();
    //ui->waveWdt->setDataLen(value);
}

LDrawCompressedWavefrom::~LDrawCompressedWavefrom()
{
    delete ui;
}

void LDrawCompressedWavefrom::resizeEvent(QResizeEvent *)
{

}


void LDrawCompressedWavefrom::setWaveData(bool flag)
{
    if(flag)
    {
       ui->waveWdt->setPointData();
    }
    else
    {

    }

}

void LDrawCompressedWavefrom::ifStartDrawWave(bool flag)
{

       setWaveData(flag);
       ui->waveWdt->ifStartDrawWave(flag);
}

void LDrawCompressedWavefrom::setDirection(DRAW_WAVE_DIRCTION direction)
{
    ui->waveWdt->setDrawWaveDirection(direction);
}

void LDrawCompressedWavefrom::setIfDrawGird(bool flag)
{
    ui->waveWdt->ifDrawGird(flag);
}

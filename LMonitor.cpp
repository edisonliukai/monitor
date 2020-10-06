#include "LMonitor.h"
#include "ui_LMonitor.h"
#include"LAppCommom.h"
#include<QTimer>
#include<QDateTime>
#include"LBottomMenuBarWidget.h"
#include<QDebug>
#include<QPropertyAnimation>
#include<QGraphicsOpacityEffect>
#include<QMouseEvent>
LMonitor::LMonitor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LMonitor)
  ,m_isDemo(false)
  ,m_isStandby(false)
  ,m_timer(new QTimer)
  ,m_menuBtnWidget(new LMenuButtonWidget)
  ,m_cchdWidget(new LCchdWidget)
  ,m_waveClickedWidget(new LWaveClickedDialogBase)
  ,m_currentButtonClicked(BOTTOM_BUTTON_OTHER)
  ,m_whichWavebeClicked(NO_WAVE_CLICKED)
  ,windowPos(0,0)
  ,mousePos(0,0)

{
    ui->setupUi(this);
    this->resize(1075,572);

   // this->setWindowIcon(QIcon(":/image/ez.jpg"));
    //this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏；
    this->setWindowTitle("LMonitor");

    //ui->timeLabel->setText("0000");
    this->setStyleSheet("background-color:black");


    initWidgetInfo();
    connect(m_timer,SIGNAL(timeout()),this,SLOT(SlotSecondEvent()));
    connect(ui->bottomWdt,SIGNAL(showMenuButtonWidget(int)),this,SLOT(SlotMenuButtonWidgetShow(int)));
    connect(ui->spo2AWdt,SIGNAL(SigWaveWidgetClicked(int)),this,SLOT(SlotWaveWidgetClicked(int)));
    connect(ui->spo2BWdt,SIGNAL(SigWaveWidgetClicked(int)),this,SLOT(SlotWaveWidgetClicked(int)));
    connect(ui->co2Wdt,SIGNAL(SigWaveWidgetClicked(int)),this,SLOT(SlotWaveWidgetClicked(int)));
    connect(m_menuBtnWidget,SIGNAL(SigBtnClicked(int)),this,SLOT(SlotDealRunModel(int)));
    m_timer->start(1000);

}

LMonitor::~LMonitor()
{
    delete ui;
    if(m_menuBtnWidget)
    {
        delete m_menuBtnWidget;
        m_menuBtnWidget = NULL;
    }
    if(m_cchdWidget)
    {
        delete m_cchdWidget;
        m_cchdWidget = NULL;
    }
}

void LMonitor::initWidgetInfo()
{
    ui->timeLabel->setStyleSheet("font-size:12px;color:white");
    ui->stackedWidget->setCurrentWidget(ui->runWdt);
    ui->ecgWdt->setDrawWaveDirection(DRAW_WAVE_FROM_RIGHT);
    ui->ecgWdt->ifStartDrawWave(true);
    ui->pulseWdt->ifStartDrawWave(true);
    ui->pulseWdt->setWaveColor(QColor("#8540BF"));
    ui->spo2AWdt->setPointColor(Qt::red);
    ui->spo2AWdt->startDrawWave();
    ui->spo2AWdt->setWaveName("spo2A");

    ui->spo2BWdt->setPointColor(Qt::yellow);
    ui->spo2BWdt->startDrawWave();
    ui->spo2BWdt->setWaveName("spo2B");

    ui->co2Wdt->setPointColor(Qt::green);
    ui->co2Wdt->startDrawWave();
    ui->co2Wdt->setWaveName("co2");
    ui->pulseWdt->setDrawWaveDirection(DRAW_WAVE_FROM_LEFT);
    if(ui->contentWdt)
    {
        m_menuBtnWidget->setParent(ui->contentWdt);
        m_menuBtnWidget->hide();
        m_waveClickedWidget->setParent(ui->contentWdt);
        m_waveClickedWidget->hide();
        //m_cchdWidget->setParent(ui->contentWdt);
        //m_cchdWidget->hide();
    }

    ui->signleWaveChart->setPointColor(Qt::cyan);
    ui->signleWaveChart->startDrawWave();


}

void LMonitor::resizeEvent(QResizeEvent *)
{

     m_menuBtnWidget->move(0,ui->contentWdt->height()/4);
     m_menuBtnWidget->setFixedSize(ui->contentWdt->width()*3/8,ui->contentWdt->height()*3/4);

     m_waveClickedWidget->move(0,ui->contentWdt->height()/4);
     m_waveClickedWidget->setFixedSize(ui->contentWdt->width()*3/8,ui->contentWdt->height()*3/4);

     //m_cchdWidget->move(0,0);
     m_cchdWidget->setFixedSize(ui->contentWdt->width()/4,ui->contentWdt->height());
}

void LMonitor::closeEvent(QCloseEvent *)
{

}

void LMonitor::mousePressEvent(QMouseEvent *event)
{
   // this->windowPos = this->pos();  // pos()是相对于窗口的，以窗口左上角为原点（去除边框）。即pos()给出的是一个相对位置坐标。而globalPos(),给出的是一个绝对坐标。
    //this->mousePos = event->globalPos();  //    globalpos()给出的坐标信息是相对于桌面的，即以桌面左上角为原点
    //this->dPos = mousePos - windowPos;
}

void LMonitor::mouseMoveEvent(QMouseEvent *)
{
   // this->move(event->globalPos() - this->dPos.);
}

void LMonitor::setCurrentTime()
{
    QDateTime current_date_time= QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("hh:mm:ss ddd");
    //ui->timeLabel->setStyleSheet("font :pointSize:50;background-color:white");
    ui->timeLabel->setText(current_date);
}

void LMonitor::setValueText()
{
    int ecg = qrand()%10+60;
    QString ecgtext = QString::number(ecg);
    ui->ecgTextLabel->setText(ecgtext);

    int spo2 = qrand()%10+90;
    QString spo2text = QString::number(spo2);
    ui->spo2TextLabel->setText(spo2text);

    int spo2B = qrand()%10+50;
    QString spo2Btext = QString::number(spo2B);
    ui->spo2BTextLabel->setText(spo2Btext);

    int co2 = qrand()%10+40;
     QString co2text  = QString::number(co2);
     ui->co2TextLabel->setText(co2text);

    int nibp1 = qrand()%10+100;
    QString nibptext1 = QString::number(nibp1);
    int nibp2 = qrand()%10+70;
    QString nibptext2 = QString::number(nibp2);
    ui->nibpValueLabel->setText(nibptext1+" / "+nibptext2);

    int  temp = qrand()%5+34;
    ui->tempWdt->setValue(temp);
    int dob = qrand()%9;
    QString tempxt = QString::number(temp);
    QString dtext = QString::number(dob);
    ui->tempLabel->setText(tempxt+"."+dtext);

    int sigle = qrand()%30+70;
    ui->sigleSpo2Widget->setValue(sigle);
    QString sigletext = QString::number(sigle);
    //ui->signleSpo2Label->setText(sigletext);
    ui->signleSpo2Label->setText(sigletext);
    ui->sigleSpo2Widget->setColorArea(0.6);

    int pr = qrand()%100+100;
    QString prtext = QString::number(pr);
    ui->signlePrLabel->setText(prtext);
    ui->signleprWidget->setValue(pr);
    ui->signleprWidget->setPieColorEnd(QColor(Qt::cyan));
    ui->signleprWidget->setRange(100,200);
    ui->signleprWidget->setPieColorStart(QColor(Qt::red));


    int pi = qrand()%9+1;
    QString pitext = QString::number(pi);
     ui->signlePiLabel->setText(pitext+".0");
     ui->signlepiWidget->setValue(pi);
     ui->signlepiWidget->setPieColorMid(QColor(Qt::green));
     ui->signlepiWidget->setRange(1,10);

     ui->signlespo2Bar->setBarColorStart(QColor(Qt::cyan));
     ui->signlespo2Bar->setBarColorMid(QColor(Qt::cyan));
     ui->signlespo2Bar->setBarColorEnd(QColor(Qt::cyan));

     int area1 = qrand()%100;
     ui->area1->setValue(area1);
     QString area1text = QString::number(area1);
     ui->area1Label->setText(area1text+"%");
     ui->area1->setColor(QColor(Qt::cyan));

     int area2 = qrand()%100;
     ui->area2->setValue(area2);
     QString area2text = QString::number(area2);
     ui->area2Label->setText(area2text+"%");
     ui->area2->setColor(QColor(Qt::green));

     int area3 = qrand()%100;
     ui->area3->setValue(area3);
     QString area3text = QString::number(area3);
     ui->area3Label->setText(area3text+"%");
     ui->area3->setColor(QColor(255, 107, 107));

     int area4 = qrand()%100;
     ui->area4->setValue(area4);
     QString area4text = QString::number(area4);
     ui->area4Label->setText(area4text+"%");
     ui->area4->setColor(QColor("#9940BF"));
     ui->standbyText->setStringText("待机中 0.0");
}

void LMonitor::SlotSecondEvent()
{

     setCurrentTime();

     setValueText();
}

void LMonitor::SlotMenuButtonWidgetShow(int i)
{
    if(!m_menuBtnWidget)
    {
        return;
    }
    BOTTOM_BUTTON_NO type = (BOTTOM_BUTTON_NO)i;

    if(type== BOTTOM_BUTTON_STANDBY) // 待机按钮，响应不同的界面。需要单独处理
    {
        if(m_menuBtnWidget->isVisible())
        {
            m_menuBtnWidget->hide();
        }
        if(!m_isStandby)
        {

            m_isStandby = true;
            ui->modeLabel->setText("當前模式: 待机模式");
            QPropertyAnimation *animation = new QPropertyAnimation(ui->standby,"windowOpacity");
            animation->setDuration(1000);
            animation->setStartValue(1);
            animation->setEndValue(0);
            animation->start();
            ui->stackedWidget->setCurrentWidget(ui->standby);

        }
        else
        {
            ui->modeLabel->setText("當前模式：實時模式");
            ui->stackedWidget->setCurrentWidget(ui->runWdt);
            m_isStandby = false;
        }
        return;
   }

   if(m_isStandby) // 如果是待机模式，那么除了待机按钮，之外的其他 底部栏按钮都要 失效无响应
   {
       return;
   }

    if(!m_menuBtnWidget->isVisible())
    {
        m_menuBtnWidget->show();

    }
    else
    {
        if(type != m_currentButtonClicked)
        {
            m_menuBtnWidget->setCurrentWidget(type);
        }
        else
        {
            m_menuBtnWidget->hide();
            m_currentButtonClicked = type;
            return;
        }

    }

    if(type == BOTTOM_BUTTON_SCREEN)
    {
        m_menuBtnWidget->setCurrentWidget(i);
        m_currentButtonClicked = BOTTOM_BUTTON_SCREEN;

    }
    else if(type == BOTTOM_BUTTON_MAIN_MENU)
    {
        m_menuBtnWidget->setCurrentWidget(i);
        m_currentButtonClicked = BOTTOM_BUTTON_MAIN_MENU;
    }
    else if(type == BOTTOM_BUTTON_PATENTION_INFO)
    {
        m_menuBtnWidget->setCurrentWidget(i);
        m_currentButtonClicked = BOTTOM_BUTTON_PATENTION_INFO;
    }
    else if( type == BOTTOM_BUTTON_REVIEW)
    {
        m_menuBtnWidget->setCurrentWidget(i);
        m_currentButtonClicked = BOTTOM_BUTTON_REVIEW;
    }

    QPropertyAnimation *animation1= new QPropertyAnimation(m_menuBtnWidget,"geometry");

    if(!animation1)
    {
        qDebug()<<"animation is null";
        return;
    }

    m_menuBtnWidget->show();
    animation1->setDuration(500);
    //animation1->setStartValue(QRect(0,-ui->widget_2->height(), ui->widget_2->width(), ui->widget_2->height()));
    animation1->setStartValue(QRect(0,ui->contentWdt->height(), ui->contentWdt->width(), ui->contentWdt->height()));
    animation1->setEndValue(m_menuBtnWidget->geometry());
    animation1->start();

}

void LMonitor::SlotWaveWidgetClicked(int i)
{
    WAVE_CLICKED_TYPE type = WAVE_CLICKED_TYPE(i);
    if(!m_waveClickedWidget->isVisible())
    {
        m_waveClickedWidget->show();
    }
    else
    {
       if(type != m_whichWavebeClicked)
       {
           m_waveClickedWidget->setCurrentWdt(type);

       }
       else
       {
          m_waveClickedWidget->hide();
          type == m_whichWavebeClicked;
          return;
       }

    }

    switch (type) {
    case SPO2A_WAVE_CLICKED:
        m_waveClickedWidget->setCurrentWdt(SPO2A_WAVE_CLICKED);
        m_whichWavebeClicked = SPO2A_WAVE_CLICKED;
        break;
    case SPO2B_WAVE_CLICKED:
        m_waveClickedWidget->setCurrentWdt(SPO2B_WAVE_CLICKED);
        m_whichWavebeClicked = SPO2B_WAVE_CLICKED;
        break;
    case CO2_WAVE_CLICKED:
        m_waveClickedWidget->setCurrentWdt(CO2_WAVE_CLICKED);
        m_whichWavebeClicked = CO2_WAVE_CLICKED;
        break;
    default:
        break;
    }

}

void LMonitor::SlotDealRunModel(int i)
{
    MENU_BUTTON_ON btnType;

    btnType = (MENU_BUTTON_ON)i;

    switch (btnType)
    {
    case MENU_BUTTON_BIG_SCREEN:
    {
        if(m_isDemo)
        {
            ui->stackedWidget_2->setCurrentWidget(ui->bigPage);
        }
        m_menuBtnWidget->hide();
        break;
    }
    case MENU_BUTTON_NORMAL_SCREEN:
    {
        if(m_isDemo)
        {
            ui->stackedWidget_2->setCurrentWidget(ui->noramlPage);
        }
        m_menuBtnWidget->hide();
        break;
    }
    case MENU_BUTTON_SINGLE_SPO2:
    {
        ui->modeLabel->setText("當前模式：工作模式");
        ui->stackedWidget->setCurrentWidget(ui->signleSpo2);

        m_menuBtnWidget->hide();
        break;
    }
    case MENU_BUTTON_CCHD:
    {
        if(!m_cchdWidget)
        {
            qDebug()<<"cchd";
            return;
        }
        if(m_cchdWidget->isVisible())
        {
            /* qDebug()<<"dan chu";
            QPropertyAnimation *animation = new QPropertyAnimation(m_cchdWidget,"windowOpacity");
            animation->setDuration(1000);
            animation->setStartValue(1);
            animation->setEndValue(0);
            animation->start();*/
            m_cchdWidget->hide();
        }
        else
        {
            m_cchdWidget->setParent(ui->contentWdt);
            QPropertyAnimation *animation2= new QPropertyAnimation(m_cchdWidget,"geometry");
            animation2->setDuration(500);
            animation2->setStartValue(QRect(0,ui->contentWdt->height(),m_cchdWidget->width(),m_cchdWidget->height()));
            //animation1->setStartValue(this->geometry());
            animation2->setEndValue(m_cchdWidget->geometry());
            //animation2->setEasingCurve(QEasingCurve::OutBounce);

            animation2->start();
            m_cchdWidget->show();
        }
        break;
    }
    case MENU_BUTTON_DEMO:
        if(!m_isDemo)
        {
            m_isDemo = true;
            ui->stackedWidget->setCurrentWidget(ui->demoWdt);
            ui->modeLabel->setText("當前模式：演示模式");
            m_menuBtnWidget->hide();
        }
        else
        {
            ui->stackedWidget->setCurrentWidget(ui->runWdt);
            m_isDemo = false;
            ui->modeLabel->setText("當前模式：實時模式");
        }
        break;
    case MENU_BUTTON_EXIT:
    {

        /*QPropertyAnimation *animation2= new QPropertyAnimation(m_menuBtnWidget,"geometry");
        animation2->setDuration(500);
        animation2->setStartValue(QRect(0,ui->contentWdt->height()/4,m_menuBtnWidget->width(),m_menuBtnWidget->height()));
        //animation1->setStartValue(this->geometry());
        //animation2->setEndValue(QRect(0,ui->contentWdt->height(), ui->contentWdt->width(), ui->contentWdt->height()));
        //animation2->setEasingCurve(QEasingCurve::OutBounce);
        animation2->setEndValue(m_menuBtnWidget->geometry());
        animation2->start();*/


        /*QPropertyAnimation *animation = new QPropertyAnimation(m_menuBtnWidget,"windowOpacity");
           animation->setDuration(500);
           animation->setStartValue(1);
           animation->setEndValue(0);
           animation->start();
        connect(animation,SIGNAL(finished()),this,SLOT(SlotDealDialogHide()));//效果显示完后关闭*/
        m_menuBtnWidget->hide();



        break;
    }
    case MENU_BUTTON_SOFTWARE_ABOUT:
    {
     m_menuBtnWidget->setCurrentWidget(BOTTOM_BUTTON_OTHER);
     break;
    }
    default:
        break;
    }
}

void LMonitor::SlotDealDialogHide()
{
    if(m_menuBtnWidget)
    {
        m_menuBtnWidget->hide();
    }

}

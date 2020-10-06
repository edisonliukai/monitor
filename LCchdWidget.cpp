#include "LCchdWidget.h"
#include "ui_LCchdWidget.h"
#include"LAppCommom.h"
#include<QDebug>
#include<QTimer>
#include<QProgressBar>
#include<QToolButton>
#include<QPropertyAnimation>

const int ONE_MEASURE_TIME = 45;// 測量一次手或者腳的時間是45秒
LCchdWidget::LCchdWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LCchdWidget)
    ,m_confirmDialog(new LConfirmDialog(this))
    ,m_isMeasuring(false)
    ,m_timer(new QTimer(this))
    ,m_num(0)
    ,m_scuccessTime(0)
{
    ui->setupUi(this);
   // m_confirmDialog->setFixedSize(this->width()/2,this->height()/2);
    //m_confirmDialog->move(this->x()/2,this->y()/2);
    //m_timer->start(1000);
   ui->spo2HandWaveWdt->setDirection(DRAW_WAVE_FROM_LEFT);
   ui->spo2FootWavwWdt->setDirection(DRAW_WAVE_FROM_LEFT);
   ui->spo2HandWaveWdt->ifStartDrawWave(false);
   ui->spo2FootWavwWdt->ifStartDrawWave(false);
   ui->spo2HandWaveWdt->setIfDrawGird(true);
   ui->spo2FootWavwWdt->setIfDrawGird(true);
    ui->progressBar->hide();
    ui->progressBar->setStyleSheet("QProgressBar{border: 2px solid grey;border-radius: 5px;text-align: center;background-color:white}");
    ui->introudcutionBtn->setStyleSheet("border: 2px solid #8f8f91;border-radius:15px;background-color:white");
    //ui->exitBtn->setStyleSheet("QToolButton{border: 2px solid #8f8f91;background-color:white}");
    ui->stackedWidget->setCurrentWidget(ui->startBtnWdt);
    connect(m_confirmDialog,SIGNAL(SigIfClearMeasureData(bool)),this,SLOT(SlotIfClearMeasureData(bool)));
    connect(ui->exitBtn,SIGNAL(clicked(bool)),this,SLOT(SlotExitBtnClicked()));
    connect(ui->startMeasureBtn,SIGNAL(clicked(bool)),this,SLOT(SlotStartMeasureBtnClicked()));
    connect(ui->confirmResultBtn,SIGNAL(clicked(bool)),this,SLOT(SlotConfirmResultBtnClicked()));
    connect(ui->remeasureBtn,SIGNAL(clicked(bool)),this,SLOT(SlotRemeasureBtnClicked()));
    connect(m_timer,SIGNAL(timeout()),this,SLOT(SlotTimeoutPro()));
    ui->progressBar->setValue(0);

}

LCchdWidget::~LCchdWidget()
{
    delete ui;
    if(m_timer)
    {
        delete m_timer;
        m_timer = NULL;
    }
    if(m_confirmDialog)
    {
        delete m_confirmDialog;
        m_confirmDialog = NULL;
    }
}

void LCchdWidget::resizeEvent(QResizeEvent *)
{
  m_confirmDialog->move(this->width()/2-m_confirmDialog->width()/2,this->height()/2-m_confirmDialog->height()/2);
}

void LCchdWidget::SlotExitBtnClicked()
{

    this->hide();
}

void LCchdWidget::SlotStartMeasureBtnClicked()
{

    if(m_scuccessTime == 2)
    {
        m_confirmDialog->show();
        //m_confirmDialog->move(this->width()/2-m_confirmDialog->width()/2,this->height()/2-m_confirmDialog->height()/2);
        return;
    }
    m_timer->start(1000);
    if(!m_isMeasuring)
    {
        if(m_scuccessTime == 0)
        {
            ui->spo2HandWaveWdt->ifStartDrawWave(true);
            ui->spo2FootWavwWdt->ifStartDrawWave(false);
        }
        else if(m_scuccessTime == 1)
        {
            ui->spo2HandWaveWdt->ifStartDrawWave(false);
            ui->spo2FootWavwWdt->ifStartDrawWave(true);
        }
        //ui->spo2HandWaveWdt->ifStartDrawWave(true);
        ui->progressBar->show();
        m_isMeasuring = true;
        ui->startMeasureBtn->setText("取消");
        ui->tipLabel->setText("測量中，請保持安靜!");
    }
    else
    {
        ui->spo2HandWaveWdt->ifStartDrawWave(false);
        ui->progressBar->hide();
        m_timer->stop();
        ui->progressBar->setValue(0);
        m_num = 0;
        m_isMeasuring = false;
        if(m_scuccessTime == 0)
        {
            ui->spo2HandWaveWdt->ifStartDrawWave(false);
            ui->startMeasureBtn->setText("開始測量");
            ui->tipLabel->setText("請連接嬰兒的右手準備測量");
        }
        else if(m_scuccessTime == 1)
        {
            ui->spo2FootWavwWdt->ifStartDrawWave(false);
            ui->startMeasureBtn->setText("開始測量");
            ui->tipLabel->setText("請連接嬰兒的腳準備測量");
        }


    }
}

void LCchdWidget::SlotConfirmResultBtnClicked()
{
      ui->stackedWidget->setCurrentWidget(ui->startBtnWdt);
      if(m_scuccessTime == 1)
      {
          ui->tipLabel->setText("請連接嬰兒的腳準備測量");
          ui->startMeasureBtn->setText("開始測量");
      }
      else if(m_scuccessTime == 2)
      {
          ui->tipLabel->setText("如質疑結果，可重新CCHD測量");
          ui->stackedWidget->setCurrentWidget(ui->startBtnWdt);
          ui->startMeasureBtn->setText("重新CCHD");
      }

}

void LCchdWidget::SlotRemeasureBtnClicked()
{
      if(m_scuccessTime == 1)
      {
         m_scuccessTime = 0;
         ui->tipLabel->setText("請連接嬰兒的右手準備測量");
      }
      else if(m_scuccessTime == 2)
      {
          m_scuccessTime = 1;
          ui->tipLabel->setText("請連接嬰兒的腳準備測量");
      }
      ui->stackedWidget->setCurrentWidget(ui->startBtnWdt);
      ui->startMeasureBtn->setText("開始測量");

}

void LCchdWidget::SlotTimeoutPro()
{
    m_num++;
    if(m_num<= ONE_MEASURE_TIME)
    {
        ui->progressBar->setValue(m_num*100/ONE_MEASURE_TIME);
    }
    else
    {
        if(m_scuccessTime == 0)
        {
          ui->spo2HandWaveWdt->ifStartDrawWave(false);
        }
        else if(m_scuccessTime == 1)
        {
          ui->spo2FootWavwWdt->ifStartDrawWave(false);
        }
        ui->progressBar->hide();
        m_isMeasuring = false;
        ui->progressBar->setValue(0);
        m_scuccessTime++;

        m_timer->stop();
        m_num = 0;

        ui->tipLabel->setText("本次測量結束");
        ui->stackedWidget->setCurrentWidget(ui->resultBtnWdt);
    }
}

void LCchdWidget::SlotIfClearMeasureData(bool ifClear)
{
    if(ifClear)
    {
        m_scuccessTime = 0;
        ui->tipLabel->setText("請連接嬰兒的右手準備測量");
        ui->startMeasureBtn->setText("開始測量");
    }
    else
    {
        m_scuccessTime = 2;
    }
}

#include "LMonitorApp.h"
#include "ui_LMonitorApp.h"
#include"LAppConfig.h"
#include<QTimer>
LMonitorApp::LMonitorApp(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LMonitorApp)
    ,m_timer(new QTimer(this))
{
    ui->setupUi(this);
    this->setWindowTitle("LMonitor");
    this->setWindowIcon(QIcon(":/image/monitor.png"));
    ui->stackedWidget->setCurrentWidget(ui->animation);
   // ui->animation->loadStartAimationPicture("123.207.249.1/data/images/kali.jpg");
    connect(m_timer,SIGNAL(timeout()),this,SLOT(appProc()));
    m_timer->start(3000);
}

LMonitorApp::~LMonitorApp()
{
    delete ui;
}

void LMonitorApp::appProc()
{
    ui->stackedWidget->setCurrentWidget(ui->monitor);
    LAppConfig::GetInstance().printData();
}

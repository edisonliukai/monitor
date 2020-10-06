#include "LMenuButtonWidget.h"
#include "ui_LMenuButtonWidget.h"
#include"LMonitor.h"
#include"LAppCommom.h"
#include<QToolButton>
#include<QDebug>
#include<QPropertyAnimation>
#include<QGraphicsOpacityEffect>
#include<QScrollBar>
LMenuButtonWidget::LMenuButtonWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LMenuButtonWidget)
{
    ui->setupUi(this);


     initmcv();

    connect(ui->exitBtn,SIGNAL(clicked(bool)),this,SLOT(SlotExitBtnClicked()));
    connect(ui->exitBtn_2,SIGNAL(clicked(bool)),this,SLOT(SlotExitBtnClicked()));
    connect(ui->paitentionExitBtn,SIGNAL(clicked(bool)),this,SLOT(SlotExitBtnClicked()));
    connect(ui->otherBedExitBtn,SIGNAL(clicked(bool)),this,SLOT(SlotExitBtnClicked()));
    // 主菜单中的按钮点击响应槽函数
    connect(ui->demoBtn,SIGNAL(clicked(bool)),this,SLOT(SlotMenuDialogButtonClicked()));
    connect(ui->aboutAuthorBtn,SIGNAL(clicked(bool)),this,SLOT(SlotMenuDialogButtonClicked()));

    connect(ui->cchdBtn,SIGNAL(clicked(bool)),this,SLOT(SlotBtnClicked()));
    connect(ui->bigScreenBtn,SIGNAL(clicked(bool)),this,SLOT(SlotBtnClicked()));
    connect(ui->noramlScreenBtn,SIGNAL(clicked(bool)),this,SLOT(SlotBtnClicked()));
    connect(ui->signleSpo2Btn,SIGNAL(clicked(bool)),this,SLOT(SlotBtnClicked()));

  initWidgetInfo();
  initButtonInfo();

}

LMenuButtonWidget::~LMenuButtonWidget()
{
    delete ui;

}

void LMenuButtonWidget::SlotBtnClicked()
{
    //ui->stackedWidget->setCurrentWidget(ui->screenWidget);
    QObject*obj = sender();
    if(!obj)
    {
        return;
    }


    if(obj->objectName() == "cchdBtn")
    {
        this->hide();
        emit SigBtnClicked(MENU_BUTTON_CCHD);
    }
    else if(obj->objectName() == "bigScreenBtn")
    {
        emit SigBtnClicked(MENU_BUTTON_BIG_SCREEN);
    }
    else if(obj->objectName() == "noramlScreenBtn")
    {
        emit SigBtnClicked(MENU_BUTTON_NORMAL_SCREEN);
    }
    else if(obj->objectName() == "signleSpo2Btn")
    {
        emit SigBtnClicked(MENU_BUTTON_SINGLE_SPO2);
    }
}

void LMenuButtonWidget::SlotMenuDialogButtonClicked()
{
    QObject*obj = sender();
    if(!obj)
    {
        return;
    }
    if(obj->objectName() == "demoBtn")
    {

        emit SigBtnClicked(MENU_BUTTON_DEMO);
        if(ui->demoBtn->text()=="演示模式")
        {
            ui->demoBtn->setText("退出演示模式");
        }
        else
        {
            ui->demoBtn->setText("演示模式");
        }
    }
    else if(obj->objectName() == "aboutAuthorBtn")
    {
         emit SigBtnClicked(MENU_BUTTON_SOFTWARE_ABOUT);
    }
}

void LMenuButtonWidget::SlotExitBtnClicked()
{
     emit SigBtnClicked(MENU_BUTTON_EXIT);
}

void LMenuButtonWidget::setCurrentWidget(int i)
{

     ui->stackedWidget->setCurrentIndex(i);

}

void LMenuButtonWidget::setCurrentWidget(QWidget *)
{

}

void LMenuButtonWidget::initButtonTextInfo()
{
    QString text[MENU_BUTTON_NUM] ={
        "演示模式",
        "屏幕选择",

    };
}
void LMenuButtonWidget::initButtonInfo()
{
    ui->meunButtonGroup->setStyleSheet("QToolButton {font-family:STLiti;font-size:16px;text-align : center; color: white;border-radius:4px; background-color: rgb(60,60,60);}");
   //ui->demoBtn->setStyleSheet("font-family:STLiti;font-size:16px;text-align : center;color: white; border-radius:4px; background-color: black");
}

void LMenuButtonWidget::initWidgetInfo()
{
    ui->tableWidget->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
      "QScrollBar::handle{background:green; border:2px solid transparent; border-radius:5px;}"
      "QScrollBar::handle:hover{background:red;}"
      "QScrollBar::sub-line{background:transparent;}"
      "QScrollBar::add-line{background:transparent;}");

      ui->tableWidget->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
      "QScrollBar::handle{background:green; border:2px solid transparent; border-radius:5px;}"
      "QScrollBar::handle:hover{background:red;}"
      "QScrollBar::sub-line{background:transparent;}"
      "QScrollBar::add-line{background:transparent;}");

      ui->scrollArea->horizontalScrollBar()->setStyleSheet("QScrollBar{background:transparent; height:10px;}"
      "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
      "QScrollBar::handle:hover{background:gray;}"
      "QScrollBar::sub-line{background:transparent;}"
      "QScrollBar::add-line{background:transparent;}");

      ui->scrollArea->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width: 10px;}"
      "QScrollBar::handle{background:lightgray; border:2px solid transparent; border-radius:5px;}"
      "QScrollBar::handle:hover{background:gray;}"
      "QScrollBar::sub-line{background:transparent;}"
      "QScrollBar::add-line{background:transparent;}");


      ui->scrollArea_2->verticalScrollBar()->setStyleSheet("QScrollBar{background:transparent; width:10px;}"
                                                                                    "QScrollBar::handle{background:green; border:2px solid transparent; border-radius:5px;}"
                                                                                    "QScrollBar::handle:hover{background:red;}"
                                                                                    "QScrollBar::sub-line{background:transparent;}"
                                                                                    "QScrollBar::add-line{background:transparent;}");


}

void LMenuButtonWidget::initmcv()
{
    mvc.setViewParent(ui->widget_13);
    mvc.initMcvInfo();
}



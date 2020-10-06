#include "LBottomMenuBarWidget.h"
#include<QToolButton>
#include<QDebug>
#include"LAppCommom.h"
LBottomMenuBarWidget::LBottomMenuBarWidget(QWidget *parent) : QWidget(parent)
 ,m_layout( new QHBoxLayout)
{

    //this->setStyleSheet("background-color:black");
    for(int i = 0;i< BUTTON_NUM;++i)
    {
       m_buttonArry[i] = NULL;

    }

    //m_menuBtnWidget->move(10,10);
    //SetButtonText();
    Init();
}

LBottomMenuBarWidget::~LBottomMenuBarWidget()
{
    for(int i = 0;i< BUTTON_NUM;++i)
    {
       delete m_buttonArry[i];
       m_buttonArry[i] = NULL;
    }
    if(m_layout)
    {
        delete m_layout;
        m_layout = NULL;
    }

}

void LBottomMenuBarWidget::resizeEvent(QResizeEvent *)
{

    for(int i = 0;i< BUTTON_NUM;++i)
    {
       m_buttonArry[i]->setFixedHeight(this->height()-2);

    }

}

void LBottomMenuBarWidget::Init()
{
    if(!m_layout)
    {
        return;
    }

    struct strButtonInfo {

        BOTTOM_BUTTON_NO strId;
        QString strText;

    } array[BUTTON_NUM] = {

        BOTTOM_BUTTON_MORE ,          " 更多 ",
        BOTTOM_BUTTON_ALARM_RESET,    "報警復位",
        BOTTOM_BUTTON_ALARM_PASUE,    "報警暫停",
        BOTTOM_BUTTON_SCREEN,         "界面設置",
        BOTTOM_BUTTON_PATENTION_INFO, "病人信息",
        BOTTOM_BUTTON_REVIEW,         "它床觀察",
        BOTTOM_BUTTON_STANDBY,        " 待機 ",
        BOTTOM_BUTTON_MAIN_MENU,      " 主菜單"
    };

    for(int i = 0;i< BUTTON_NUM;++i)
    {
       m_buttonArry[i] = new QToolButton(this);
       m_buttonArry[i]->setText(array[i].strText);
       m_buttonArry[i]->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
       //m_buttonArry[i]->setStyleSheet("font: STLiti; PointSize font-size:20px; color: white; background-color: rgb(46, 52, 54);");
       m_buttonArry[i]->setStyleSheet("font-family:STLiti;font-size:20px;text-align : center;color: white; background-color: rgb(46, 52, 54)");
       m_buttonArry[i]->setObjectName(QString::number(i));
       m_layout->addWidget(m_buttonArry[i]);
       connect(m_buttonArry[i],SIGNAL(clicked(bool)),this,SLOT(SlotBottomButtonClicked()));
    }

    m_layout->setContentsMargins(0,0,0,0);
    m_layout->setSpacing(0);
    this->setLayout(m_layout);

}

void LBottomMenuBarWidget::SlotBottomButtonClicked()
{
    QObject *obj = sender();
    if(!obj)
    {

        return;
    }

    for(int i =BOTTOM_BUTTON_SCREEN;i<BOTTOM_BUTTON_OTHER;++i)
    {
       if(obj->objectName()== QString::number(i))
        {

            emit showMenuButtonWidget(i);

        }
    }
}

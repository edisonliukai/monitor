/************************************************************************************************
* program   :  Monitor                                                                          *
* autor     :  edison                                                                           *
* File Description : 底部菜单栏窗体类                                                              *
* start date:  2020-8-20                                                                        *
*                                                                                               *
* **********************************************************************************************/
#pragma once
#include <QObject>
#include <QWidget>
#include<QHBoxLayout>
#include<QPushButton>
#include<QToolButton>
#include"LMenuButtonWidget.h"
const int BUTTON_NUM = 8;
class LBottomMenuBarWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LBottomMenuBarWidget(QWidget *parent = nullptr);
   ~LBottomMenuBarWidget();
public:
    void Init();

    void resizeEvent(QResizeEvent *);

signals:
  void showMenuButtonWidget(int i);
public slots:
   void SlotBottomButtonClicked();
private:

    QHBoxLayout  * m_layout;
    QToolButton  * m_buttonArry[BUTTON_NUM];
    QString        m_buttonText[BUTTON_NUM];
};

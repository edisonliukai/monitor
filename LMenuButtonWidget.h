/************************************************************************************************
* program   :  Monitor                                                                          *
* autor     :  edison                                                                           *
* File Description : 点击主菜单按钮弹出框                                                              *
* start date:  2020-8-20                                                                        *
*                                                                                               *
* **********************************************************************************************/
#pragma once
#include <QWidget>
#include<QTableView>
#include<QStandardItemModel>
#include"LAppForMvc.h"
const int MENU_BUTTON_NUM = 30;
namespace Ui {
class LMenuButtonWidget;
}

class LMenuButtonWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LMenuButtonWidget(QWidget *parent = 0);
    ~LMenuButtonWidget();
public:
    void setCurrentWidget(int i);
    void setCurrentWidget(QWidget*);
    void initButtonTextInfo();
    void initButtonInfo();
    void initWidgetInfo();
    //void initMCVInfo();
    void initmcv();
signals:
    void SigBtnClicked(int);
public slots:
    void SlotBtnClicked();
    void SlotExitBtnClicked();// 退出按钮命令
    void SlotMenuDialogButtonClicked(); // 主菜单中的按钮响应

private:
    Ui::LMenuButtonWidget *ui;
    QString   m_buttonText[MENU_BUTTON_NUM];
   // QTableView *m_tableView;
   // QStandardItemModel *m_model;
    LAppForMvc mvc;
};



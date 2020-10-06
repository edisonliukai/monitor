 /************************************************************************************************
 * program   :  Monitor                                                                          *
 * autor     :  edison                                                                           *
 * File Description : 软件主界面窗体类                                                              *
 * start date:  2020-8-20                                                                        *
 * Author's original intention: This software is for learning only, without any commercial use   *
 * statement :  All interpretation rights of this software belong to Mr. Liu Kai                 *
 * **********************************************************************************************/
#pragma once
#include <QWidget>
#include"LMenuButtonWidget.h"
#include"LCchdWidget.h"
#include"LAppCommom.h"
#include"LStartAnimation.h"
#include"LWaveClickedDialogBase.h"
namespace Ui {
class LMonitor;
}

class LMonitor : public QWidget
{
    Q_OBJECT

public:
    explicit LMonitor(QWidget *parent = 0);
    ~LMonitor();
public:
    void resizeEvent(QResizeEvent *);
    void closeEvent(QCloseEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void setCurrentTime();
    void setValueText();
    void initWidgetInfo();
private slots:
    // 秒事件函数
    void SlotSecondEvent();
    void SlotMenuButtonWidgetShow(int );
    void SlotDealRunModel(int);
    void SlotDealDialogHide();
    void SlotWaveWidgetClicked(int);
public:
    bool m_isDemo; // 是否是演示模式
    bool m_isStandby;// 是否是待机模式
private:
    Ui::LMonitor *ui;
    QTimer*m_timer;
    LMenuButtonWidget* m_menuBtnWidget;
    LCchdWidget      * m_cchdWidget;
    LWaveClickedDialogBase * m_waveClickedWidget;
    BOTTOM_BUTTON_NO   m_currentButtonClicked; // 用於標記底部欄中當前被點擊的按鈕序號
    WAVE_CLICKED_TYPE  m_whichWavebeClicked;   // 标记哪一种类型的波形界面被点击
    QPoint  windowPos;
    QPoint  mousePos;
    QPoint  dPos;
};


/************************************************************************************************
* program   :  Monitor                                                                          *
* autor     :  edison                                                                           *
* File Description : CCHD 篩選主界面                                                              *
* start date:  2020-8-23                                                                        *
*                                                                                               *
* **********************************************************************************************/
#pragma once
#include <QWidget>
#include"LConfirmDialog.h"
namespace Ui {
class LCchdWidget;
}

class LCchdWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LCchdWidget(QWidget *parent = 0);
    ~LCchdWidget();
public:
    void resizeEvent(QResizeEvent *);
public slots:
    void SlotExitBtnClicked();
    void SlotStartMeasureBtnClicked();
    void SlotConfirmResultBtnClicked();
    void SlotRemeasureBtnClicked();
    void SlotTimeoutPro();
    void SlotIfClearMeasureData(bool);
private:
    Ui::LCchdWidget *ui;
    LConfirmDialog *m_confirmDialog;
    bool m_isMeasuring;
    QTimer  *m_timer;
    int      m_num;
    int      m_scuccessTime;
};



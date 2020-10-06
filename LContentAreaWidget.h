/************************************************************************************************
* program   :  Monitor                                                                          *
* autor     :  edison                                                                           *
* File Description : 内容区窗体类                                                              *
* start date:  2020-8-20                                                                        *
*                                                                                               *
* **********************************************************************************************/
#pragma once
#include <QObject>
#include <QWidget>
#include<QRect>
#include<QVBoxLayout>
#include"CustomControl/LSmoothWaveform/LSmoothWaveform.h"
const int ITEM_NUM = 4; //  内容区域的主界面显示 co2 spo2 spo2B ECG 4个的波形和参数
// 测量参数结构体 包含参数区域，文字，背景闪烁，背景闪烁颜色等等

typedef struct strParameterItem
{
    QString m_name;
    QRect m_spo2Rect;
    QRect m_prRect;
    QRect m_valueRect;
    QRect m_hRect;
    QRect m_lRect;
    QRect m_piRect;
    QRect m_spcoRect;
    QRect m_spospmetRect;
    bool  m_isflash;
    QColor  m_color;

}PARAMETER_ITEM;


class LContentAreaWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LContentAreaWidget(QWidget *parent = nullptr);
    ~LContentAreaWidget();
public:
    //void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
    void InitWidget();
    void InitItem(PARAMETER_ITEM&item); // 初始化参数项目
signals:

public slots:

private:
  //PARAMETER_ITEM  m_spo2Item;
    QVBoxLayout * m_layout;
    LSmoothWaveform   *m_waveChartArry[ITEM_NUM];
};


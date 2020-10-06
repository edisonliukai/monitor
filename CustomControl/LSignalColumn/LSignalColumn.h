/************************************************************************************************
* program   :  Monitor                                                                          *
* autor     :  edison                                                                           *
* File Description : 信号柱控件                                                                   *
* start date:  2020-8-23                                                                        *
*                                                                                               *
* **********************************************************************************************/
#pragma once
#include <QWidget>
class LSignalColumn : public QWidget
{
    Q_OBJECT


public:
    explicit LSignalColumn(QWidget *parent = 0);
     ~LSignalColumn();
protected:
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawBarBg(QPainter *painter);
    void drawBar(QPainter *painter);

private:
    int value;                      //目标值
    int step;                       //步长
    int space;                      //间距
    int padding;                    //间隔
    int radius;                     //圆角角度
    QTimer     *m_timer;
    QColor bgColorStart;            //背景渐变开始颜色
    QColor bgColorEnd;              //背景渐变结束颜色

    QColor barBgColor;              //进度背景颜色
    QColor barColorStart;           //进度渐变开始颜色
    QColor barColorMid;             //进度渐变中间颜色
    QColor barColorEnd;             //进度渐变结束颜色

public:
    int getValue()                  const;
    int getStep()                   const;
    int getSpace()                  const;
    int getPadding()                const;
    int getRadius()                 const;

    QColor getBgColorStart()        const;
    QColor getBgColorEnd()          const;

    QColor getBarBgColor()          const;
    QColor getBarColorStart()       const;
    QColor getBarColorMid()         const;
    QColor getBarColorEnd()         const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    //设置目标值
    void setValue(int value);
    //设置步长
    void setStep(int step);
    //设置间距
    void setSpace(int space);
    //设置间隔
    void setPadding(int padding);
    //设置圆角角度
    void setRadius(int radius);

    //设置背景颜色
    void setBgColorStart(QColor bgColorStart);
    void setBgColorEnd(QColor bgColorEnd);

    //设置柱状颜色
    void setBarBgColor(QColor barBgColor);
    void setBarColorStart(QColor barColorStart);
    void setBarColorMid(QColor barColorMid);
    void setBarColorEnd(QColor barColorEnd);
    void SlotTimeoutPro();
};


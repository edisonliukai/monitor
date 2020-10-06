/************************************************************************************************
* program   :  Monitor                                                                          *
* autor     :  edison                                                                           *
* File Description : 柱状统计图控件                                                               *
* start date:  2020-8-20                                                                        *
*                                                                                               *
* **********************************************************************************************/
#pragma once
#include <QWidget>
class LBarChart : public QWidget
{
    Q_OBJECT    
    

public:
    explicit LBarChart(QWidget *parent = 0);
    ~LBarChart();

protected:
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawRuler(QPainter *painter);
    void drawBarBg(QPainter *painter);
    void drawBar(QPainter *painter);

private:    
    double minValue;                //最小值
    double maxValue;                //最大值
    double value;                   //目标值
    int precision;                  //精确度,小数点后几位

    int longStep;                   //长线条等分步长
    int shortStep;                  //短线条等分步长
    int space;                      //间距

    bool animation;                 //是否启用动画显示
    double animationStep;           //动画显示时步长

    QColor bgColorStart;            //背景渐变开始颜色
    QColor bgColorEnd;              //背景渐变结束颜色
    QColor lineColor;               //线条颜色
    QColor barBgColor;              //柱状背景色
    QColor barColor;                //柱状颜色

    bool reverse;                   //是否倒退
    double currentValue;            //当前值
    QTimer *timer;                  //定时器绘制动画
    QRectF barRect;                 //柱状图区域

private slots:
    void updateValue();

public:

    void  setColor(QColor color);
    double getMinValue()            const;
    double getMaxValue()            const;
    double getValue()               const;
    int getPrecision()              const;

    int getLongStep()               const;
    int getShortStep()              const;
    int getSpace()                  const;

    bool getAnimation()             const;
    double getAnimationStep()       const;

    QColor getBgColorStart()        const;
    QColor getBgColorEnd()          const;
    QColor getLineColor()           const;
    QColor getBarBgColor()          const;
    QColor getBarColor()            const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    //设置最大最小值-范围值
    void setRange(double minValue, double maxValue);
    void setRange(int minValue, int maxValue);

    //设置最大最小值
    void setMinValue(double minValue);
    void setMaxValue(double maxValue);

    //设置目标值
    void setValue(double value);
    void setValue(int value);

    //设置精确度
    void setPrecision(int precision);
    //设置线条等分步长
    void setLongStep(int longStep);
    void setShortStep(int shortStep);
    //设置间距
    void setSpace(int space);

    //设置是否启用动画显示
    void setAnimation(bool animation);
    //设置动画显示的步长
    void setAnimationStep(double animationStep);

    //设置背景颜色
    void setBgColorStart(const QColor &bgColorStart);
    void setBgColorEnd(const QColor &bgColorEnd);
    //设置线条颜色
    void setLineColor(const QColor &lineColor);
    //设置柱状颜色
    void setBarBgColor(const QColor &barBgColor);

    void setBarColor(QColor barColor);

Q_SIGNALS:
    void valueChanged(double value);
};


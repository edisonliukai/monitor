/************************************************************************************************
* program   :  Monitor                                                                          *
* autor     :  edison                                                                           *
* File Description : 温度计控件                                                              *
* start date:  2020-8-20                                                                        *
*                                                                                               *
* **********************************************************************************************/
#pragma once
#include <QWidget>

class LThermometer : public QWidget
{
    Q_OBJECT
    

public:
    enum BarPosition {
        BarPosition_Left = 0,       //左侧显示
        BarPosition_Right = 1,      //右侧显示
        BarPosition_Center = 2      //居中显示
    };

    enum TickPosition {
        TickPosition_Null = 0,      //不显示
        TickPosition_Left = 1,      //左侧显示
        TickPosition_Right = 2,     //右侧显示
        TickPosition_Both = 3       //两侧显示
    };

    explicit LThermometer(QWidget *parent = 0);
    ~LThermometer();

protected:
    void resizeEvent(QResizeEvent *);
    void paintEvent(QPaintEvent *);
    void drawBg(QPainter *painter);
    void drawBarBg(QPainter *painter);
    void drawRuler(QPainter *painter, int type);
    void drawBar(QPainter *painter);
    void drawValue(QPainter *painter);

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

    bool showUserValue;             //显示用户设定值
    double userValue;               //用户设定值
    QColor userValueColor;          //用户设定值颜色

    QColor bgColorStart;            //背景渐变开始颜色
    QColor bgColorEnd;              //背景渐变结束颜色
    QColor lineColor;               //线条颜色
    QColor barBgColor;              //柱状背景色
    QColor barColor;                //柱状颜色

    BarPosition barPosition;        //柱状条位置
    TickPosition tickPosition;      //刻度尺位置

    int barWidth;                   //水银柱宽度
    int barHeight;                  //水银柱高度
    int radius;                     //水银柱底部圆半径
    int targetX;                    //目标X坐标
    QRectF barRect;                 //柱状区域
    QRectF circleRect;              //底部圆区域

    bool reverse;                   //是否倒退
    double currentValue;            //当前值
    QTimer *timer;                  //定时器绘制动画

private slots:
    void updateValue();

public:
    double getMinValue()            const;
    double getMaxValue()            const;
    double getValue()               const;

    int getPrecision()              const;
    int getLongStep()               const;
    int getShortStep()              const;
    int getSpace()                  const;

    bool getAnimation()             const;
    double getAnimationStep()       const;

    bool getShowUserValue()         const;
    double getUserValue()           const;
    QColor getUserValueColor()      const;

    QColor getBgColorStart()        const;
    QColor getBgColorEnd()          const;
    QColor getLineColor()           const;
    QColor getBarBgColor()          const;
    QColor getBarColor()            const;

    BarPosition getBarPosition()    const;
    TickPosition getTickPosition()  const;

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

    //设置是否显示用户设定值
    void setShowUserValue(bool showUserValue);

    //设置用户值
    void setUserValue(double userValue);
    void setUserValue(int userValue);

    //设置用户设定值颜色
    void setUserValueColor(const QColor &userValueColor);

    //设置背景颜色
    void setBgColorStart(const QColor &bgColorStart);
    void setBgColorEnd(const QColor &bgColorEnd);

    //设置线条颜色
    void setLineColor(const QColor &lineColor);

    //设置柱状颜色
    void setBarBgColor(const QColor &barBgColor);
    void setBarColor(const QColor &barColor);

    //设置柱状条位置
    void setBarPosition(const BarPosition &barPosition);

    //设置刻度尺位置
    void setTickPosition(const TickPosition &tickPosition);

Q_SIGNALS:
    void valueChanged(double value);
};



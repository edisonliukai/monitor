/************************************************************************************************
* program   :  Monitor                                                                          *
* autor     :  edison                                                                           *
* File Description : 电池控件类                                                              *
* start date:  2020-8-20                                                                        *
*                                                                                               *
* **********************************************************************************************/
#pragma once
#include <QWidget>
class LBattery : public QWidget
{
    Q_OBJECT    


public:
    explicit LBattery(QWidget *parent = 0);
    ~LBattery();

protected:
    void paintEvent(QPaintEvent *);
    void drawBorder(QPainter *painter);
    void drawBg(QPainter *painter);
    void drawHead(QPainter *painter);

private slots:
    void updateValue();

private:    
    double minValue;                //最小值
    double maxValue;                //最大值
    double value;                   //目标电量
    double alarmValue;              //电池电量警戒值

    double step;                    //每次移动的步长
    int borderRadius;               //边框圆角角度
    int bgRadius;                   //背景进度圆角角度
    int headRadius;                 //头部圆角角度

    QColor borderColorStart;        //边框渐变开始颜色
    QColor borderColorEnd;          //边框渐变结束颜色

    QColor alarmColorStart;         //电池低电量时的渐变开始颜色
    QColor alarmColorEnd;           //电池低电量时的渐变结束颜色

    QColor normalColorStart;        //电池正常电量时的渐变开始颜色
    QColor normalColorEnd;          //电池正常电量时的渐变结束颜色

    bool isForward;                 //是否往前移
    double currentValue;            //当前电量
    QRectF batteryRect;             //电池主体区域
    QTimer *timer;                  //绘制定时器
    QTimer *valueTimer;
public:    
    double getMinValue()            const;
    double getMaxValue()            const;
    double getValue()               const;
    double getAlarmValue()          const;

    double getStep()                const;
    int getBorderRadius()           const;
    int getBgRadius()               const;
    int getHeadRadius()             const;

    QColor getBorderColorStart()    const;
    QColor getBorderColorEnd()      const;

    QColor getAlarmColorStart()     const;
    QColor getAlarmColorEnd()       const;

    QColor getNormalColorStart()    const;
    QColor getNormalColorEnd()      const;

    QSize sizeHint()                const;
    QSize minimumSizeHint()         const;

public Q_SLOTS:
    //设置范围值
    void setRange(double minValue, double maxValue);
    void setRange(int minValue, int maxValue);

    //  设置当前值
    void setCurrentValue();
    //设置最大最小值
    void setMinValue(double minValue);
    void setMaxValue(double maxValue);

    //设置电池电量值
    void setValue(double value);
    void setValue(int value);

    //设置电池电量警戒值
    void setAlarmValue(double alarmValue);
    void setAlarmValue(int alarmValue);

    //设置步长
    void setStep(double step);
    void setStep(int step);

    //设置边框圆角角度
    void setBorderRadius(int borderRadius);
    //设置背景圆角角度
    void setBgRadius(int bgRadius);
    //设置头部圆角角度
    void setHeadRadius(int headRadius);

    //设置边框渐变颜色
    void setBorderColorStart(const QColor &borderColorStart);
    void setBorderColorEnd(const QColor &borderColorEnd);

    //设置电池电量报警时的渐变颜色
    void setAlarmColorStart(const QColor &alarmColorStart);
    void setAlarmColorEnd(const QColor &alarmColorEnd);

    //设置电池电量正常时的渐变颜色
    void setNormalColorStart(const QColor &normalColorStart);
    void setNormalColorEnd(const QColor &normalColorEnd);

Q_SIGNALS:
    void valueChanged(double value);
};



/************************************************************************************************
* program   :  Monitor                                                                          *
* autor     :  edison                                                                           *
* File Description : 光滑波形控件                                                                 *
* start date:  2020-8-20                                                                        *
*                                                                                               *
* **********************************************************************************************/
#pragma once
#include <QWidget>
#include <QList>
#include <QPointF>
#include <QPainterPath>
#include "LWaveClickedDialogBase.h"
class LSmoothCurveCreator
{
public:
    static QPainterPath createSmoothCurve(const QVector<QPointF> &points);

private:
    static void calculateFirstControlPoints(double *&result, const double *rhs, int n);
    static void calculateControlPoints(const QVector<QPointF> &knots, QVector<QPointF> *firstControlPoints, QVector<QPointF> *secondControlPoints);
};

class LSmoothWaveform : public QWidget
{
	Q_OBJECT

public:
    explicit LSmoothWaveform(QWidget *parent = 0);
     ~LSmoothWaveform();
public:
    void mousePressEvent(QMouseEvent *);

	void paintEvent(QPaintEvent *);
	void drawBg(QPainter *painter);
	void drawBox(QPainter *painter);
	void drawText(QPainter *painter);
	void drawTitle(QPainter *painter);
	void drawPoint(QPainter *painter);
    void setWaveName(QString wavename);
    QString getWaveName();

signals:
    void SigWaveWidgetClicked(int);
private slots:
	void updateData();

private:
    QString m_waveName;
    QRectF pointRect;               //绘制数据区域
    QVector<double> listData;       //数据集合

    double minValue;                //最小值
    double maxValue;                //最大值
    double xStep;                   //x轴步长
    double yStep;                   //y轴步长

    double space;                   //间隔
    QString title;                  //标题
    bool smooth;                    //是否平滑
    bool showHLine;                 //是否显示横线
    bool showPoint;                 //是否显示坐标点
    bool showPointBg;               //是否显示坐标背景

    QColor bgColorStart;            //背景渐变开始颜色
    QColor bgColorEnd;              //背景渐变结束颜色
    QColor textColor;               //文字颜色
    QColor pointColor;              //坐标点颜色
    QTimer   *m_timer;

public:
	double getMinValue()            const;
	double getMaxValue()            const;
	double getXStep()               const;
	double getYStep()               const;

	double getSpace()               const;
	QString getTitle()              const;
    bool getSmooth()                const;
    bool getShowHLine()             const;
	bool getShowPoint()             const;
	bool getShowPointBg()           const;

	QColor getBgColorStart()        const;
	QColor getBgColorEnd()          const;
	QColor getTextColor()           const;
	QColor getPointColor()          const;

	QSize sizeHint()                const;
	QSize minimumSizeHint()         const;

public Q_SLOTS:
	//添加和设置数据数据
	void addData(double data);
	void setData(QVector<double> data);
	void clearData();
    void addDataToWave();
    void startDrawWave();
	//设置范围值及步长
	void setMinValue(double minValue);
	void setMaxValue(double maxValue);
	void setXStep(double xStep);
	void setYStep(double yStep);

	//设置间隔
	void setSpace(double space);
	//设置标题
	void setTitle(const QString &title);
    //设置是否平滑曲线
    void setSmooth(bool smooth);
	//设置显示横线
	void setShowHLine(bool showHLine);
	//设置显示坐标点
	void setShowPoint(bool showPoint);
	//设置显示坐标背景
	void setShowPointBg(bool showPointBg);

	//设置颜色
	void setBgColorStart(const QColor &bgColorStart);
	void setBgColorEnd(const QColor &bgColorEnd);
	void setTextColor(const QColor &textColor);
	void setPointColor(const QColor &pointColor);
};



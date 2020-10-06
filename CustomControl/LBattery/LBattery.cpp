#pragma execution_character_set("utf-8")

#include "LBattery.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"
#include<QDebug>
LBattery::LBattery(QWidget *parent) : QWidget(parent)
{
    minValue = 0;
    maxValue = 100;
    value = 0;
    alarmValue = 30;
    step = 0.5;

    borderRadius = 8;
    bgRadius = 5;
    headRadius = 3;

    borderColorStart = QColor(100, 100, 100);
    borderColorEnd = QColor(80, 80, 80);
    alarmColorStart = QColor(250, 118, 113);
    alarmColorEnd = QColor(204, 38, 38);
    normalColorStart = QColor(50, 205, 51);
    normalColorEnd = QColor(60, 179, 133);

    isForward = false;
    currentValue = 0;

    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    valueTimer = new QTimer(this);
    connect(valueTimer, SIGNAL(timeout()), this, SLOT(setCurrentValue()));
    valueTimer->start(1000);
}

LBattery::~LBattery()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void LBattery::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制边框
    drawBorder(&painter);
    //绘制背景
    drawBg(&painter);
    //绘制头部
    drawHead(&painter);
}

void LBattery::drawBorder(QPainter *painter)
{
    painter->save();

    double headWidth = width() / 10;
    double batteryWidth = width() - headWidth;

    //绘制电池边框
    QPointF topLeft(5, 5);
    QPointF bottomRight(batteryWidth, height() - 5);
    batteryRect = QRectF(topLeft, bottomRight);

    painter->setPen(QPen(borderColorStart, 5));
    painter->setBrush(Qt::NoBrush);
    painter->drawRoundedRect(batteryRect, borderRadius, borderRadius);

    painter->restore();
}

void LBattery::drawBg(QPainter *painter)
{
    painter->save();

    QLinearGradient batteryGradient(QPointF(0, 0), QPointF(0, height()));
    if (currentValue <= alarmValue) {
        batteryGradient.setColorAt(0.0, alarmColorStart);
        batteryGradient.setColorAt(1.0, alarmColorEnd);
    } else {
        batteryGradient.setColorAt(0.0, normalColorStart);
        batteryGradient.setColorAt(1.0, normalColorEnd);
    }

    int margin = qMin(width(), height()) / 20;
    double unit = (batteryRect.width() - (margin * 2)) / 100;
    double width = currentValue * unit;
    QPointF topLeft(batteryRect.topLeft().x() + margin, batteryRect.topLeft().y() + margin);
    QPointF bottomRight(width + margin + 5, batteryRect.bottomRight().y() - margin);
    QRectF rect(topLeft, bottomRight);

    painter->setPen(Qt::NoPen);
    painter->setBrush(batteryGradient);
    painter->drawRoundedRect(rect, bgRadius, bgRadius);

    painter->restore();
}

void LBattery::drawHead(QPainter *painter)
{
    painter->save();

    QPointF headRectTopLeft(batteryRect.topRight().x(), height() / 3);
    QPointF headRectBottomRight(width(), height() - height() / 3);
    QRectF headRect(headRectTopLeft, headRectBottomRight);

    QLinearGradient headRectGradient(headRect.topLeft(), headRect.bottomLeft());
    headRectGradient.setColorAt(0.0, borderColorStart);
    headRectGradient.setColorAt(1.0, borderColorEnd);

    painter->setPen(Qt::NoPen);
    painter->setBrush(headRectGradient);
    painter->drawRoundedRect(headRect, headRadius, headRadius);

    painter->restore();
}

void LBattery::updateValue()
{

    /*if (isForward) {
        currentValue -= step;

        if (currentValue <= value) {
            timer->stop();
        }
    } else {
        currentValue += step;

        if (currentValue >= value) {
            timer->stop();
        }
    }

    this->update();*/
}

double LBattery::getMinValue() const
{
    return this->minValue;
}

double LBattery::getMaxValue() const
{
    return this->maxValue;
}

double LBattery::getValue() const
{
    return this->value;
}

double LBattery::getAlarmValue() const
{
    return this->alarmValue;
}

double LBattery::getStep() const
{
    return this->step;
}

int LBattery::getBorderRadius() const
{
    return this->borderRadius;
}

int LBattery::getBgRadius() const
{
    return this->bgRadius;
}

int LBattery::getHeadRadius() const
{
    return this->headRadius;
}

QColor LBattery::getBorderColorStart() const
{
    return this->borderColorStart;
}

QColor LBattery::getBorderColorEnd() const
{
    return this->borderColorEnd;
}

QColor LBattery::getAlarmColorStart() const
{
    return this->alarmColorStart;
}

QColor LBattery::getAlarmColorEnd() const
{
    return this->alarmColorEnd;
}

QColor LBattery::getNormalColorStart() const
{
    return this->normalColorStart;
}

QColor LBattery::getNormalColorEnd() const
{
    return this->normalColorEnd;
}

QSize LBattery::sizeHint() const
{
    return QSize(150, 80);
}

void LBattery::setCurrentValue()
{
    int num = qrand()%100;
    currentValue = (double)num;

    update();
}
QSize LBattery::minimumSizeHint() const
{
    return QSize(30, 10);
}

void LBattery::setRange(double minValue, double maxValue)
{
    //如果最小值大于或者等于最大值则不设置
    if (minValue >= maxValue) {
        return;
    }

    this->minValue = minValue;
    this->maxValue = maxValue;

    //如果目标值不在范围值内,则重新设置目标值
    //值小于最小值则取最小值,大于最大值则取最大值
    if (value < minValue) {
        setValue(minValue);
    } else if (value > maxValue) {
        setValue(maxValue);
    }

    this->update();
}

void LBattery::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void LBattery::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void LBattery::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void LBattery::setValue(double value)
{
    //值和当前值一致则无需处理
    if (value == this->value) {
        return;
    }

    //值小于最小值则取最小值,大于最大值则取最大值
    if (value < minValue) {
        value = minValue;
    } else if (value > maxValue) {
        value = maxValue;
    }

    if (value > currentValue) {
        isForward = false;
    } else if (value < currentValue) {
        isForward = true;
    } else {
        return;
    }

    this->value = value;
    this->update();
    emit valueChanged(value);
    timer->start();
}

void LBattery::setValue(int value)
{
    setValue((double)value);
}

void LBattery::setAlarmValue(double alarmValue)
{
    if (this->alarmValue != alarmValue) {
        this->alarmValue = alarmValue;
        this->update();
    }
}

void LBattery::setAlarmValue(int alarmValue)
{
    setAlarmValue((double)alarmValue);
}

void LBattery::setStep(double step)
{
    if (this->step != step) {
        this->step = step;
        this->update();
    }
}

void LBattery::setStep(int step)
{
    setStep((double)step);
}

void LBattery::setBorderRadius(int borderRadius)
{
    if (this->borderRadius != borderRadius) {
        this->borderRadius = borderRadius;
        this->update();
    }
}

void LBattery::setBgRadius(int bgRadius)
{
    if (this->bgRadius != bgRadius) {
        this->bgRadius = bgRadius;
        this->update();
    }
}

void LBattery::setHeadRadius(int headRadius)
{
    if (this->headRadius != headRadius) {
        this->headRadius = headRadius;
        this->update();
    }
}

void LBattery::setBorderColorStart(const QColor &borderColorStart)
{
    if (this->borderColorStart != borderColorStart) {
        this->borderColorStart = borderColorStart;
        this->update();
    }
}

void LBattery::setBorderColorEnd(const QColor &borderColorEnd)
{
    if (this->borderColorEnd != borderColorEnd) {
        this->borderColorEnd = borderColorEnd;
        this->update();
    }
}

void LBattery::setAlarmColorStart(const QColor &alarmColorStart)
{
    if (this->alarmColorStart != alarmColorStart) {
        this->alarmColorStart = alarmColorStart;
        this->update();
    }
}

void LBattery::setAlarmColorEnd(const QColor &alarmColorEnd)
{
    if (this->alarmColorEnd != alarmColorEnd) {
        this->alarmColorEnd = alarmColorEnd;
        this->update();
    }
}

void LBattery::setNormalColorStart(const QColor &normalColorStart)
{
    if (this->normalColorStart != normalColorStart) {
        this->normalColorStart = normalColorStart;
        this->update();
    }
}

void LBattery::setNormalColorEnd(const QColor &normalColorEnd)
{
    if (this->normalColorEnd != normalColorEnd) {
        this->normalColorEnd = normalColorEnd;
        this->update();
    }
}


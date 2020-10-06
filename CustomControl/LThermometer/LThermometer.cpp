﻿#pragma execution_character_set("utf-8")

#include "LThermometer.h"
#include "qpainter.h"
#include "qpainterpath.h"
#include "qtimer.h"
#include "qdebug.h"

LThermometer::LThermometer(QWidget *parent) : QWidget(parent)
{

    minValue = 34.0;
    maxValue = 40.0;
    value = 37.2;

    precision = 0;
    longStep = 10;
    shortStep = 2;
    space = 10;

    animation = false;
    animationStep = 1.0;

    showUserValue = false;
    userValue = 80;
    userValueColor = QColor(255, 107, 107);

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);
    lineColor = QColor(255, 255, 255);

    //barBgColor = QColor(230, 230, 230);
    //barColor = QColor(100, 184, 255);
    barBgColor = QColor(Qt::white);
    barColor = QColor("#A279C5");
    barPosition = BarPosition_Center;
    tickPosition = TickPosition_Both;

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(1);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Arial", 9));
    resizeEvent(NULL);
}

LThermometer::~LThermometer()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void LThermometer::resizeEvent(QResizeEvent *)
{
    //水银柱底部圆的半径为宽高中最小值的 5分之一
    radius = qMin(width(), height()) / 3;
    //水银柱的宽度为底部圆的直径的 3分之一
    barWidth = (radius * 2) / 3;
    barHeight = height() - radius * 2;

    if (barPosition == BarPosition_Left) {
        targetX = width() / 4;
    } else if (barPosition == BarPosition_Right) {
        targetX = width() / 1.3;
    } else if (barPosition == BarPosition_Center) {
        targetX = width() / 2;
    }

    setValue(value);
}

void LThermometer::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);

    //绘制标尺及刻度尺

    //drawRuler(&painter, 0);
    //drawRuler(&painter, 1);


    //绘制水银柱背景,包含水银柱底部圆
    drawBarBg(&painter);

    //绘制当前水银柱,包含水银柱底部圆
    drawBar(&painter);

    //绘制当前值
    drawValue(&painter);
}

void LThermometer::drawBg(QPainter *painter)
{
    /*painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPointF(0, 0), QPointF(0, height()));
    bgGradient.setColorAt(0.0, bgColorStart);
    bgGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();*/
}

void LThermometer::drawBarBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barBgColor);

    int barX = targetX - barWidth / 2;
    int barY = space;
    QRectF barRect(barX, barY, barWidth, barHeight);

    int circleX = targetX - radius;
    //偏移 2 个像素,使得看起来边缘完整
    int circleY = height() - radius * 2 - 2;
    int circleWidth = radius * 2;
    QRectF circleRect(circleX, circleY, circleWidth, circleWidth);

    QPainterPath path;
    path.addRect(barRect);
    path.addEllipse(circleRect);
    path.setFillRule(Qt::WindingFill);
    painter->drawPath(path);
    painter->restore();
}

void LThermometer::drawRuler(QPainter *painter, int type)
{
    painter->save();
    painter->setPen(lineColor);

    int barPercent = barWidth / 8;

    if (barPercent < 2) {
        barPercent = 2;
    }

    //绘制纵向标尺刻度
    double length = height() - 2 * space - 2 * radius;
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);

    //长线条短线条长度
    int longLineLen = 10;
    int shortLineLen = 7;

    //绘制纵向标尺线 偏移 5 像素
    int offset = barWidth / 2 + 5;

    //左侧刻度尺需要重新计算
    if (type == 0) {
        offset = -offset;
        longLineLen = -longLineLen;
        shortLineLen = -shortLineLen;
    }

    double initX = targetX + offset;
    double initY = space + barPercent;
    QPointF topPot(initX, initY);
    QPointF bottomPot(initX, height() - 2 * radius - 5);
    painter->drawLine(topPot, bottomPot);

    //根据范围值绘制刻度值及刻度值
    for (int i = maxValue; i >= minValue; i = i - shortStep) {
        if (i % longStep == 0) {
            //绘制长线条
            QPointF leftPot(initX + longLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);

            //绘制文字
            QString strValue = QString("%1").arg((double)i, 0, 'f', precision);
            double fontHeight = painter->fontMetrics().height();

            if (type == 0) {
                QRect textRect(initX - 45, initY - fontHeight / 3, 30, 15);
                painter->drawText(textRect, Qt::AlignRight, strValue);
            } else if (type == 1) {
                QRect textRect(initX + longLineLen + 5, initY - fontHeight / 3, 30, 15);
                painter->drawText(textRect, Qt::AlignLeft, strValue);
            }
        } else {
            //绘制短线条
            QPointF leftPot(initX + shortLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);
        }

        initY += increment * shortStep;
    }

    painter->restore();
}

void LThermometer::drawBar(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(barColor);

    //计算在背景宽度的基础上缩小的百分比, 至少为 2
    int barPercent = barWidth / 8;
    int circlePercent = radius / 6;

    if (barPercent < 2) {
        barPercent = 2;
    }

    if (circlePercent < 2) {
        circlePercent = 2;
    }

    //标尺刻度高度
    double length = height() - 2 * space - 2 * radius;
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    //计算标尺的高度
    int rulerHeight = height() - 1 * space - 2 * radius;

    int barX = targetX - barWidth / 2;
    int barY = rulerHeight - (currentValue - minValue) * increment;
    barRect = QRectF(barX + barPercent, barY + barPercent, barWidth - barPercent * 2, barHeight + radius - barY);

    int circleX = targetX - radius;
    //偏移 2 个像素,使得看起来边缘完整
    int circleY = height() - radius * 2 - 2;
    int circleWidth = radius * 2 - circlePercent * 2;
    circleRect = QRectF(circleX + circlePercent, circleY + circlePercent, circleWidth, circleWidth);

    QPainterPath path;
    path.addRect(barRect);
    path.addEllipse(circleRect);
    path.setFillRule(Qt::WindingFill);
    painter->drawPath(path);

    //绘制用户设定值三角号
    if (showUserValue) {
        if (tickPosition == TickPosition_Left || tickPosition == TickPosition_Both) {
            QPolygon pts;
            int offset = 15;
            double initX = targetX - (barWidth / 2 + 5);
            double initY = rulerHeight - (userValue - minValue) * increment;
            pts.append(QPoint(initX, initY));
            pts.append(QPoint(initX - offset, initY - offset / 2));
            pts.append(QPoint(initX - offset, initY + offset / 2));
            painter->setBrush(userValueColor);
            painter->drawPolygon(pts);
        }

        if (tickPosition == TickPosition_Right || tickPosition == TickPosition_Both) {
            QPolygon pts;
            int offset = 15;
            double initX = targetX + (barWidth / 2 + 5);
            double initY = rulerHeight - (userValue - minValue) * increment;
            pts.append(QPoint(initX, initY));
            pts.append(QPoint(initX + offset, initY - offset / 2));
            pts.append(QPoint(initX + offset, initY + offset / 2));
            painter->setBrush(userValueColor);
            painter->drawPolygon(pts);
        }
    }

    painter->restore();
}

void LThermometer::drawValue(QPainter *painter)
{
    painter->save();

    QFont font;
    font.setPixelSize(circleRect.width() * 0.55);
    painter->setFont(font);
    painter->setPen(Qt::white);
    painter->drawText(circleRect, Qt::AlignCenter, QString("%1").arg(currentValue));

    painter->restore();
}

double LThermometer::getMinValue() const
{
    return this->minValue;
}

double LThermometer::getMaxValue() const
{
    return this->maxValue;
}

double LThermometer::getValue() const
{
    return this->value;
}

int LThermometer::getPrecision() const
{
    return this->precision;
}

int LThermometer::getLongStep() const
{
    return this->longStep;
}

int LThermometer::getShortStep() const
{
    return this->shortStep;
}

int LThermometer::getSpace() const
{
    return this->space;
}

bool LThermometer::getAnimation() const
{
    return this->animation;
}

double LThermometer::getAnimationStep() const
{
    return this->animationStep;
}

bool LThermometer::getShowUserValue() const
{
    return this->showUserValue;
}

double LThermometer::getUserValue() const
{
    return this->userValue;
}

QColor LThermometer::getUserValueColor() const
{
    return this->userValueColor;
}

QColor LThermometer::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor LThermometer::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor LThermometer::getLineColor() const
{
    return this->lineColor;
}

QColor LThermometer::getBarBgColor() const
{
    return this->barBgColor;
}

QColor LThermometer::getBarColor() const
{
    return this->barColor;
}

LThermometer::BarPosition LThermometer::getBarPosition() const
{
    return this->barPosition;
}

LThermometer::TickPosition LThermometer::getTickPosition() const
{
    return this->tickPosition;
}

QSize LThermometer::sizeHint() const
{
    return QSize(130, 350);
}

QSize LThermometer::minimumSizeHint() const
{
    return QSize(20, 50);
}

void LThermometer::setRange(double minValue, double maxValue)
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

void LThermometer::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void LThermometer::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void LThermometer::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void LThermometer::setValue(double value)
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

    if (value > this->value) {
        reverse = false;
    } else if (value < this->value) {
        reverse = true;
    }

    this->value = value;
    emit valueChanged(value);

    if (!animation) {
        currentValue = this->value;
        this->update();
    } else {
        timer->start();
    }
}

void LThermometer::setValue(int value)
{
    setValue((double)value);
}

void LThermometer::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        this->update();
    }
}

void LThermometer::setLongStep(int longStep)
{
    //短步长不能超过长步长
    if (longStep < shortStep) {
        return;
    }

    if (this->longStep != longStep) {
        this->longStep = longStep;
        this->update();
    }
}

void LThermometer::setShortStep(int shortStep)
{
    //短步长不能超过长步长
    if (longStep < shortStep) {
        return;
    }

    if (this->shortStep != shortStep) {
        this->shortStep = shortStep;
        this->update();
    }
}

void LThermometer::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        this->update();
    }
}

void LThermometer::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        this->update();
    }
}

void LThermometer::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        this->update();
    }
}

void LThermometer::setShowUserValue(bool showUserValue)
{
    if (this->showUserValue != showUserValue) {
        this->showUserValue = showUserValue;
        this->update();
    }
}

void LThermometer::setUserValue(double userValue)
{
    //值小于最小值或者值大于最大值或者值和当前值一致则无需处理
    if (userValue < minValue || userValue > maxValue) {
        return;
    }

    if (this->userValue != userValue) {
        this->userValue = userValue;
        this->update();
    }
}

void LThermometer::setUserValue(int userValue)
{
    setUserValue((double)userValue);
}

void LThermometer::setUserValueColor(const QColor &userValueColor)
{
    if (this->userValueColor != userValueColor) {
        this->userValueColor = userValueColor;
        this->update();
    }
}

void LThermometer::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        this->update();
    }
}

void LThermometer::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        this->update();
    }
}

void LThermometer::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        this->update();
    }
}

void LThermometer::setBarBgColor(const QColor &barBgColor)
{
    if (this->barBgColor != barBgColor) {
        this->barBgColor = barBgColor;
        this->update();
    }
}

void LThermometer::setBarColor(const QColor &barColor)
{
    if (this->barColor != barColor) {
        this->barColor = barColor;
        this->update();
    }
}

void LThermometer::setBarPosition(const LThermometer::BarPosition &barPosition)
{
    if (this->barPosition != barPosition) {
        this->barPosition = barPosition;
        this->update();
    }
}

void LThermometer::setTickPosition(const LThermometer::TickPosition &tickPosition)
{
    if (this->tickPosition != tickPosition) {
        this->tickPosition = tickPosition;
        this->update();
    }
}

void LThermometer::updateValue()
{
   //int objvalue = qrand()%30;
    //setValue(objvalue);
    if (!reverse) {
        if (currentValue >= value) {
            currentValue = value;
            timer->stop();
        } else {
            currentValue += animationStep;
        }
    } else {
        if (currentValue <= value) {
            currentValue = value;
            timer->stop();
        } else {
            currentValue -= animationStep;
        }
    }

    this->update();
}

#pragma execution_character_set("utf-8")

#include "LBarChart.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

LBarChart::LBarChart(QWidget *parent) : QWidget(parent)
{    
    minValue = 0;
    maxValue = 100;
    value = 0;

    precision = 0;
    longStep = 10;
    shortStep = 1;
    space = 20;

    animation = false;
    animationStep = 0.5;

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);
    lineColor = QColor(255, 255, 255);

    barBgColor = QColor(250, 250, 250);
    barColor = QColor(100, 184, 255);

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));

    setFont(QFont("Arial", 8));
}

LBarChart::~LBarChart()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void LBarChart::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
   // drawBg(&painter);
    //绘制标尺
    //drawRuler(&painter);
    //绘制柱状背景
    drawBarBg(&painter);
    //绘制柱状
    drawBar(&painter);
}

void LBarChart::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::red);
    QLinearGradient bgGradient(QPointF(0, 0), QPointF(0, height()));
    bgGradient.setColorAt(0.0, bgColorStart);
    bgGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void LBarChart::drawRuler(QPainter *painter)
{
    painter->save();
    painter->setPen(lineColor);

    //绘制纵向标尺线 20的长度为刻度尺文字的宽度
    double initX = space + 20;
    double initY = space;
    QPointF topPot(initX, initY);
    QPointF bottomPot(initX, height() - space);
    painter->drawLine(topPot, bottomPot);

    //绘制纵向标尺刻度
    double length = height() - 2 * space;
    //计算每一格移动多少
    double increment = length / (maxValue - minValue);
    //长线条短线条长度
    int longLineLen = 10;
    int shortLineLen = 7;

    //根据范围值绘制刻度值及刻度值
    for (int i = maxValue; i >= minValue; i = i - shortStep) {
        if (i % longStep == 0) {
            QPointF leftPot(initX + longLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);

            QString strValue = QString("%1").arg((double)i, 0, 'f', precision);
            double fontWidth = painter->fontMetrics().width(strValue);
            double fontHeight = painter->fontMetrics().height();
            QPointF textPot(initX - fontWidth - 5, initY + fontHeight / 3);
            painter->drawText(textPot, strValue);
        } else {
            if (i % (longStep / 2) == 0) {
                shortLineLen = 7;
            } else {
                shortLineLen = 4;
            }

            QPointF leftPot(initX + shortLineLen, initY);
            QPointF rightPot(initX, initY);
            painter->drawLine(leftPot, rightPot);
        }

        initY += increment * shortStep;
    }

    painter->restore();
}

void LBarChart::drawBarBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    //20的长度为刻度尺文字的宽度 15为刻度尺到柱状图的宽度
    double initX = space ;
    QPointF topLeftPot(initX, space);
    QPointF bottomRightPot(width() - space , height() - space);
    barRect = QRectF(topLeftPot, bottomRightPot);

    painter->setBrush(barBgColor);
    painter->drawRect(barRect);
    painter->restore();
}

void LBarChart::drawBar(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);

    double barHeight = barRect.height();
    double increment = (double)barHeight / (maxValue - minValue);
    double initY = (currentValue - minValue) * increment;

    QPointF topLeftPot(barRect.topLeft().x(), barRect.bottomLeft().y() - initY);
    QPointF bottomRightPot(barRect.bottomRight());
    QRectF currentRect(topLeftPot, bottomRightPot);

    painter->setBrush(barColor);
    painter->drawRect(currentRect);
    painter->restore();
}


double LBarChart::getMinValue() const
{
    return this->minValue;
}

void LBarChart::setColor(QColor Color)
{
    barColor = Color;
}
double LBarChart::getMaxValue() const
{
    return this->maxValue;
}

double LBarChart::getValue() const
{
    return this->value;
}

int LBarChart::getPrecision() const
{
    return this->precision;
}

int LBarChart::getLongStep() const
{
    return this->longStep;
}

int LBarChart::getShortStep() const
{
    return this->shortStep;
}

int LBarChart::getSpace() const
{
    return this->space;
}

bool LBarChart::getAnimation() const
{
    return this->animation;
}

double LBarChart::getAnimationStep() const
{
    return this->animationStep;
}

QColor LBarChart::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor LBarChart::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor LBarChart::getLineColor() const
{
    return this->lineColor;
}

QColor LBarChart::getBarBgColor() const
{
    return this->barBgColor;
}

QColor LBarChart::getBarColor() const
{
    return this->barColor;
}

QSize LBarChart::sizeHint() const
{
    return QSize(100, 350);
}

QSize LBarChart::minimumSizeHint() const
{
    return QSize(20, 50);
}

void LBarChart::setRange(double minValue, double maxValue)
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

void LBarChart::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void LBarChart::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void LBarChart::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void LBarChart::setValue(double value)
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

void LBarChart::setValue(int value)
{
    setValue((double)value);
}

void LBarChart::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        this->update();
    }
}

void LBarChart::setLongStep(int longStep)
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

void LBarChart::setShortStep(int shortStep)
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

void LBarChart::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        this->update();
    }
}

void LBarChart::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        this->update();
    }
}

void LBarChart::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        this->update();
    }
}

void LBarChart::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        this->update();
    }
}

void LBarChart::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        this->update();
    }
}

void LBarChart::setLineColor(const QColor &lineColor)
{
    if (this->lineColor != lineColor) {
        this->lineColor = lineColor;
        this->update();
    }
}

void LBarChart::setBarBgColor(const QColor &barBgColor)
{
    if (this->barBgColor != barBgColor) {
        this->barBgColor = barBgColor;
        this->update();
    }
}

void LBarChart::setBarColor(QColor barColor)
{
    if (this->barColor != barColor) {
        this->barColor = barColor;
        this->update();
    }
}

void LBarChart::updateValue()
{
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

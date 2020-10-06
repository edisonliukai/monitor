#pragma execution_character_set("utf-8")

#include "LRingIndicator.h"
#include "qpainter.h"
#include "qpainterpath.h"
#include "qmath.h"
#include "qtimer.h"
#include "qdebug.h"

LRingIndicator::LRingIndicator(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("background-color:black");
    minValue = 70;
    maxValue = 100;
    value = 50;
    precision = 0;

    scaleMajor = 3;
    scaleMinor = 3;
    startAngle = 120;
    endAngle = 120;

    animation = false;
    animationStep = 0.5;

    outerCircleColor = QColor(80, 80, 80);
    innerCircleColor = QColor(60, 60, 60);

    pieColorStart = QColor(24, 189, 155);
    pieColorMid = QColor(218, 218, 0);
    pieColorEnd = QColor(255, 107, 107);

    coverCircleColor = QColor(Qt::black);
    scaleColor = QColor(255, 255, 255);
    pointerColor = QColor(255, 107, 107);
    centerCircleColor = QColor(250, 250, 250);
    textColor = QColor(0, 0, 0);

    showOverlay = true;
    overlayColor = QColor(255, 255, 255, 60);

    circleWidth = 15;
    pieStyle = PieStyle_Three;
    pointerStyle = PointerStyle_Indicator;

    reverse = false;
    currentValue = 0;
    timer = new QTimer(this);
    timer->setInterval(10);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateValue()));
    m_pix = 0.7;
    setFont(QFont("Arial", 8));
}

LRingIndicator::~LRingIndicator()
{
    if (timer->isActive()) {
        timer->stop();
    }
}

void LRingIndicator::paintEvent(QPaintEvent *)
{

    int width = this->width();
    int height = this->height();
    int side = qMin(width, height);

    //绘制准备工作,启用反锯齿,平移坐标轴中心,等比例缩放
    QPainter painter(this);
    QRectF rect = QRectF(0,0,this->width(),this->height());
    painter.fillRect(rect,Qt::black);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
    painter.translate(width / 2, height / 2);
    painter.scale(side / 80.0, side / 80.0);


    drawColorPie(&painter);

    drawCoverCircle(&painter);


    drawScaleNum(&painter);



    drawPointerTriangle(&painter);



}




void LRingIndicator::drawColorPie(QPainter *painter)
{
    int radius = 60;
    painter->save();
    painter->setPen(Qt::NoPen);

    QRectF rect(-radius, -radius+50, radius * 2, radius * 2);

    if (pieStyle == PieStyle_Three) {
        //计算总范围角度,根据占比例自动计算三色圆环范围角度
        //可以更改比例
        double angleAll = 360.0 - startAngle - endAngle;
        double angleStart = angleAll * m_pix;
        double angleMid = angleAll * (1-m_pix)/2;
        double angleEnd = angleAll * (1-m_pix)/2;

        //增加偏移量使得看起来没有脱节
        int offset = 3;

        //绘制开始饼圆
        painter->setBrush(pieColorStart);
        painter->drawPie(rect, (270 - startAngle - angleStart) * 16, angleStart * 16);

        //绘制中间饼圆
        painter->setBrush(pieColorMid);
        painter->drawPie(rect, (270 - startAngle - angleStart - angleMid) * 16 + offset, angleMid * 16);

        //绘制结束饼圆
        painter->setBrush(pieColorEnd);
        painter->drawPie(rect, (270 - startAngle - angleStart - angleMid - angleEnd) * 16 + offset * 2, angleEnd * 16);
    } else if (pieStyle == PieStyle_Current) {
        //计算总范围角度,当前值范围角度,剩余值范围角度
        double angleAll = 360.0 - startAngle - endAngle;
        double angleCurrent = angleAll * ((currentValue - minValue) / (maxValue - minValue));
        double angleOther = angleAll - angleCurrent;

        //绘制当前值饼圆
        painter->setBrush(pieColorStart);
        painter->drawPie(rect, (270 - startAngle - angleCurrent) * 16, angleCurrent * 16);

        //绘制剩余值饼圆
        painter->setBrush(pieColorEnd);
        painter->drawPie(rect, (270 - startAngle - angleCurrent - angleOther) * 16, angleOther * 16);
    }

    painter->restore();
}

void LRingIndicator::drawCoverCircle(QPainter *painter)
{
    int radius = 50;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(coverCircleColor);
    painter->drawEllipse(-radius, -radius+50, radius * 2, radius * 2);
    painter->restore();
}

void LRingIndicator::drawScale(QPainter *painter)
{
    int radius = 72;
    painter->save();

    painter->rotate(startAngle);
    int steps = (scaleMajor * scaleMinor);
    double angleStep = (360.0 - startAngle - endAngle) / steps;

    QPen pen;
    pen.setColor(scaleColor);
    pen.setCapStyle(Qt::RoundCap);

    for (int i = 0; i <= steps; i++) {
        if (i % scaleMinor == 0) {
            pen.setWidthF(1.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 10, 0, radius);
        } else {
            pen.setWidthF(0.5);
            painter->setPen(pen);
            painter->drawLine(0, radius - 5, 0, radius);
        }

        painter->rotate(angleStep);
    }

    painter->restore();
}

void LRingIndicator::drawScaleNum(QPainter *painter)
{
    int radius = 70;
    painter->save();
    painter->setPen(scaleColor);

    double startRad = (360 - startAngle - 90) * (M_PI / 180);
    double deltaRad = (360 - startAngle - endAngle) * (M_PI / 180) / scaleMajor;

    for (int i = 0; i <= scaleMajor; i++) {
        double sina = qSin(startRad - i * deltaRad);
        double cosa = qCos(startRad - i * deltaRad);
        double value = 1.0 * i * ((maxValue - minValue) / scaleMajor) + minValue;

        QString strValue = QString("%1").arg((double)value, 0, 'f', precision);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        int x = radius * cosa - textWidth / 2;
        int y = -radius * sina + textHeight / 4+50;
        painter->drawText(x, y, strValue);
    }

    painter->restore();
}

void LRingIndicator::drawPointerCircle(QPainter *painter)
{
    int radius = 6;
    int offset = 30;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawEllipse(-radius, radius + offset, radius * 2, radius * 2);

    painter->restore();
}

void LRingIndicator::drawPointerIndicator(QPainter *painter)
{
    int radius = 75;
    painter->save();
    painter->setOpacity(0.8);
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void LRingIndicator::drawPointerIndicatorR(QPainter *painter)
{
    int radius = 75;
    painter->save();
    painter->setOpacity(1.0);

    QPen pen;
    pen.setWidth(1);
    pen.setColor(pointerColor);
    painter->setPen(pen);
    painter->setBrush(pointerColor);

    QPolygon pts;
    pts.setPoints(3, -5, 0, 5, 0, 0, radius);

    painter->rotate(startAngle);
    double degRotate = (360.0 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);
    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    //增加绘制圆角直线,与之前三角形重叠,形成圆角指针
    pen.setCapStyle(Qt::RoundCap);
    pen.setWidthF(4);
    painter->setPen(pen);
    painter->drawLine(0, 0, 0, radius);

    painter->restore();
}

void LRingIndicator::drawPointerTriangle(QPainter *painter)
{
    int radius = 10;
    int offset = 38;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);
    painter->translate(0,50);
    QPolygon pts;
    pts.setPoints(3, -5, 0 + offset, 5, 0 + offset, 0, radius + offset);

    painter->rotate(startAngle);
    double degRotate = (360 - startAngle - endAngle) / (maxValue - minValue) * (currentValue - minValue);


    painter->rotate(degRotate);
    painter->drawConvexPolygon(pts);

    painter->restore();
}

void LRingIndicator::drawRoundCircle(QPainter *painter)
{
    int radius = circleWidth + 3;
    painter->save();
    painter->setOpacity(0.8);
    painter->setPen(Qt::NoPen);
    painter->setBrush(pointerColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void LRingIndicator::drawCenterCircle(QPainter *painter)
{
    int radius = circleWidth;
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setBrush(centerCircleColor);
    painter->drawEllipse(-radius, -radius, radius * 2, radius * 2);
    painter->restore();
}

void LRingIndicator::drawValue(QPainter *painter)
{
    int radius = 100;
    painter->save();
    painter->setPen(textColor);

    QFont font;
    font.setPixelSize(18);
    painter->setFont(font);

    QRectF textRect(-radius, -radius, radius * 2, radius * 2);
    QString strValue = QString("%1").arg((double)currentValue, 0, 'f', precision);
    painter->drawText(textRect, Qt::AlignCenter, strValue);

    painter->restore();
}

void LRingIndicator::drawOverlay(QPainter *painter)
{
    if (!showOverlay) {
        return;
    }

    int radius = 90;
    painter->save();
    painter->setPen(Qt::NoPen);

    QPainterPath smallCircle;
    QPainterPath bigCircle;
    radius -= 1;
    smallCircle.addEllipse(-radius, -radius, radius * 2, radius * 2);
    radius *= 2;
    bigCircle.addEllipse(-radius, -radius + 140, radius * 2, radius * 2);

    //高光的形状为小圆扣掉大圆的部分
    QPainterPath highlight = smallCircle - bigCircle;

    QLinearGradient linearGradient(0, -radius / 2, 0, 0);
    overlayColor.setAlpha(100);
    linearGradient.setColorAt(0.0, overlayColor);
    overlayColor.setAlpha(30);
    linearGradient.setColorAt(1.0, overlayColor);
    painter->setBrush(linearGradient);
    painter->rotate(-20);
    painter->drawPath(highlight);

    painter->restore();
}

void LRingIndicator::updateValue()
{
    if (!reverse) {
        if (currentValue >= value) {
            timer->stop();
        } else {
            currentValue += animationStep;
        }
    } else {
        if (currentValue <= value) {
            timer->stop();
        } else {
            currentValue -= animationStep;
        }
    }

    this->update();
}

void LRingIndicator::setColorArea(double value)
{
   m_pix = value;
}

double LRingIndicator::getMinValue() const
{
    return this->minValue;
}

double LRingIndicator::getMaxValue() const
{
    return this->maxValue;
}

double LRingIndicator::getValue() const
{
    return this->value;
}

int LRingIndicator::getPrecision() const
{
    return this->precision;
}

int LRingIndicator::getScaleMajor() const
{
    return this->scaleMajor;
}

int LRingIndicator::getScaleMinor() const
{
    return this->scaleMinor;
}

int LRingIndicator::getStartAngle() const
{
    return this->startAngle;
}

int LRingIndicator::getEndAngle() const
{
    return this->endAngle;
}

bool LRingIndicator::getAnimation() const
{
    return this->animation;
}

double LRingIndicator::getAnimationStep() const
{
    return this->animationStep;
}

QColor LRingIndicator::getOuterCircleColor() const
{
    return this->outerCircleColor;
}

QColor LRingIndicator::getInnerCircleColor() const
{
    return this->innerCircleColor;
}

QColor LRingIndicator::getPieColorStart() const
{
    return this->pieColorStart;
}

QColor LRingIndicator::getPieColorMid() const
{
    return this->pieColorMid;
}

QColor LRingIndicator::getPieColorEnd() const
{
    return this->pieColorEnd;
}

QColor LRingIndicator::getCoverCircleColor() const
{
    return this->coverCircleColor;
}

QColor LRingIndicator::getScaleColor() const
{
    return this->scaleColor;
}

QColor LRingIndicator::getPointerColor() const
{
    return this->pointerColor;
}

QColor LRingIndicator::getCenterCircleColor() const
{
    return this->centerCircleColor;
}

QColor LRingIndicator::getTextColor() const
{
    return this->textColor;
}

bool LRingIndicator::getShowOverlay() const
{
    return this->showOverlay;
}

QColor LRingIndicator::getOverlayColor() const
{
    return this->overlayColor;
}

int LRingIndicator::getCircleWidth() const
{
    return this->circleWidth;
}

LRingIndicator::PieStyle LRingIndicator::getPieStyle() const
{
    return this->pieStyle;
}

LRingIndicator::PointerStyle LRingIndicator::getPointerStyle() const
{
    return this->pointerStyle;
}

QSize LRingIndicator::sizeHint() const
{
    return QSize(200, 200);
}

QSize LRingIndicator::minimumSizeHint() const
{
    return QSize(50, 50);
}

void LRingIndicator::setRange(double minValue, double maxValue)
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

void LRingIndicator::setRange(int minValue, int maxValue)
{
    setRange((double)minValue, (double)maxValue);
}

void LRingIndicator::setMinValue(double minValue)
{
    setRange(minValue, maxValue);
}

void LRingIndicator::setMaxValue(double maxValue)
{
    setRange(minValue, maxValue);
}

void LRingIndicator::setValue(double value)
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

void LRingIndicator::setValue(int value)
{
    setValue((double)value);
}

void LRingIndicator::setPrecision(int precision)
{
    //最大精确度为 3
    if (precision <= 3 && this->precision != precision) {
        this->precision = precision;
        this->update();
    }
}

void LRingIndicator::setScaleMajor(int scaleMajor)
{
    if (scaleMajor > 0 && this->scaleMajor != scaleMajor) {
        this->scaleMajor = scaleMajor;
        this->update();
    }
}

void LRingIndicator::setScaleMinor(int scaleMinor)
{
    if (scaleMinor > 0 && this->scaleMinor != scaleMinor) {
        this->scaleMinor = scaleMinor;
        this->update();
    }
}

void LRingIndicator::setStartAngle(int startAngle)
{
    if (this->startAngle != startAngle) {
        this->startAngle = startAngle;
        this->update();
    }
}

void LRingIndicator::setEndAngle(int endAngle)
{
    if (this->endAngle != endAngle) {
        this->endAngle = endAngle;
        this->update();
    }
}

void LRingIndicator::setAnimation(bool animation)
{
    if (this->animation != animation) {
        this->animation = animation;
        this->update();
    }
}

void LRingIndicator::setAnimationStep(double animationStep)
{
    if (this->animationStep != animationStep) {
        this->animationStep = animationStep;
        this->update();
    }
}

void LRingIndicator::setOuterCircleColor(const QColor &outerCircleColor)
{
    if (this->outerCircleColor != outerCircleColor) {
        this->outerCircleColor = outerCircleColor;
        this->update();
    }
}

void LRingIndicator::setInnerCircleColor(const QColor &innerCircleColor)
{
    if (this->innerCircleColor != innerCircleColor) {
        this->innerCircleColor = innerCircleColor;
        this->update();
    }
}

void LRingIndicator::setPieColorStart(const QColor &pieColorStart)
{
    if (this->pieColorStart != pieColorStart) {
        this->pieColorStart = pieColorStart;
        this->update();
    }
}

void LRingIndicator::setPieColorMid(const QColor &pieColorMid)
{
    if (this->pieColorMid != pieColorMid) {
        this->pieColorMid = pieColorMid;
        this->update();
    }
}

void LRingIndicator::setPieColorEnd(const QColor &pieColorEnd)
{
    if (this->pieColorEnd != pieColorEnd) {
        this->pieColorEnd = pieColorEnd;
        this->update();
    }
}

void LRingIndicator::setCoverCircleColor(const QColor &coverCircleColor)
{
    if (this->coverCircleColor != coverCircleColor) {
        this->coverCircleColor = coverCircleColor;
        this->update();
    }
}

void LRingIndicator::setScaleColor(const QColor &scaleColor)
{
    if (this->scaleColor != scaleColor) {
        this->scaleColor = scaleColor;
        this->update();
    }
}

void LRingIndicator::setPointerColor(const QColor &pointerColor)
{
    if (this->pointerColor != pointerColor) {
        this->pointerColor = pointerColor;
        this->update();
    }
}

void LRingIndicator::setCenterCircleColor(const QColor &centerCircleColor)
{
    if (this->centerCircleColor != centerCircleColor) {
        this->centerCircleColor = centerCircleColor;
        this->update();
    }
}

void LRingIndicator::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();
    }
}

void LRingIndicator::setShowOverlay(bool showOverlay)
{
    if (this->showOverlay != showOverlay) {
        this->showOverlay = showOverlay;
        this->update();
    }
}

void LRingIndicator::setOverlayColor(const QColor &overlayColor)
{
    if (this->overlayColor != overlayColor) {
        this->overlayColor = overlayColor;
        this->update();
    }
}

void LRingIndicator::setCircleWidth(int circleWidth)
{
    if (this->circleWidth != circleWidth) {
        this->circleWidth = circleWidth;
        this->update();
    }
}

void LRingIndicator::setPieStyle(const LRingIndicator::PieStyle &pieStyle)
{
    if (this->pieStyle != pieStyle) {
        this->pieStyle = pieStyle;
        this->update();
    }
}

void LRingIndicator::setPointerStyle(const LRingIndicator::PointerStyle &pointerStyle)
{
    if (this->pointerStyle != pointerStyle) {
        this->pointerStyle = pointerStyle;
        this->update();
    }
}

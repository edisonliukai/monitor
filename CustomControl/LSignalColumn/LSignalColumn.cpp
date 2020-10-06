#pragma execution_character_set("utf-8")

#include "LSignalColumn.h"
#include "qpainter.h"
#include "qtimer.h"
#include "qdebug.h"

LSignalColumn::LSignalColumn(QWidget *parent) : QWidget(parent)
  ,m_timer(new QTimer(this))
{
    value = 0;
    step = 10;
    space = 2;
    padding = 3;
    radius = 2;

    bgColorStart = QColor(100, 100, 100);
    bgColorEnd = QColor(60, 60, 60);

   /* barBgColor = QColor(167, 167, 167);
    barColorStart = QColor(85, 255, 0);
    barColorMid = QColor(249, 216, 47);
    barColorEnd = QColor(249, 107, 24);*/

    barColorStart = QColor(Qt::yellow);
    barColorMid = QColor(Qt::yellow);
    barColorEnd = QColor(Qt::yellow);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(SlotTimeoutPro()));
    m_timer->start(1000);
}

LSignalColumn::~LSignalColumn()
{
   if(m_timer)
   {
       delete m_timer;
       m_timer =NULL;
   }
}

void LSignalColumn::SlotTimeoutPro()
{
    int value = qrand()%7+3;
    setValue(value);
}
void LSignalColumn::paintEvent(QPaintEvent *)
{
    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);

    //绘制背景
    drawBg(&painter);
    //绘制进度背景
    drawBarBg(&painter);
    //绘制进度
    drawBar(&painter);
}

void LSignalColumn::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient bgGradient(QPointF(0, 0), QPointF(0, height()));
    bgGradient.setColorAt(0.0, bgColorStart);
    bgGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(bgGradient);
    painter->drawRect(rect());
    painter->restore();
}

void LSignalColumn::drawBarBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setOpacity(0.4);
    painter->setBrush(barBgColor);

    //每格的步长等于高度 - 上下两个间隔 - (格数-1)*间隔  最后除以格数
    double increment = (double)(height() - (space * 2) - (step - 1) * padding) / step;
    double initY = space;

    for (int i = 0; i < step; i++) {
        QRectF barBgRect(QPointF(space, initY), QPointF(width() - space, initY + increment));
        painter->drawRoundedRect(barBgRect, radius, radius);
        initY += increment + padding;
    }

    painter->restore();
}

void LSignalColumn::drawBar(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    painter->setOpacity(1.0);

    QLinearGradient barGradient(QPointF(0, height() - space), QPointF(0, space));
    barGradient.setColorAt(0.0, barColorStart);
    barGradient.setColorAt(0.5, barColorMid);
    barGradient.setColorAt(1.0, barColorEnd);
    painter->setBrush(barGradient);

    //每格的步长等于高度 - 上下两个间隔 - (格数-1)*间隔  最后除以格数
    double increment = (double)(height() - (space * 2) - (step - 1) * padding) / step;
    double initY = padding * (step - value) + (step - value) * increment + space ;

    for (int i = 0; i < value; i++) {
        QRectF barRect(QPointF(space, initY), QPointF(width() - space, initY + increment));
        painter->drawRoundedRect(barRect, radius, radius);
        initY += increment + padding;
    }

    painter->restore();
}

int LSignalColumn::getValue() const
{
    return this->value;
}

int LSignalColumn::getStep() const
{
    return this->step;
}

int LSignalColumn::getSpace() const
{
    return this->space;
}

int LSignalColumn::getPadding() const
{
    return this->padding;
}

int LSignalColumn::getRadius() const
{
    return this->radius;
}

QColor LSignalColumn::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor LSignalColumn::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor LSignalColumn::getBarBgColor() const
{
    return this->barBgColor;
}

QColor LSignalColumn::getBarColorStart() const
{
    return this->barColorStart;
}

QColor LSignalColumn::getBarColorMid() const
{
    return this->barColorMid;
}

QColor LSignalColumn::getBarColorEnd() const
{
    return this->barColorEnd;
}

QSize LSignalColumn::sizeHint() const
{
    return QSize(100, 300);
}

QSize LSignalColumn::minimumSizeHint() const
{
    return QSize(10, 30);
}

void LSignalColumn::setValue(int value)
{
    if (this->value != value && value <= step) {
        this->value = value;
        this->update();
    }
}

void LSignalColumn::setStep(int step)
{
    if (this->step != step && value <= step) {
        this->step = step;
        this->update();
    }
}

void LSignalColumn::setSpace(int space)
{
    if (this->space != space) {
        this->space = space;
        this->update();
    }
}

void LSignalColumn::setPadding(int padding)
{
    if (this->padding != padding) {
        this->padding = padding;
        this->update();
    }
}

void LSignalColumn::setRadius(int radius)
{
    if (this->radius != radius) {
        this->radius = radius;
        this->update();
    }
}

void LSignalColumn::setBgColorStart(QColor bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        this->update();
    }
}

void LSignalColumn::setBgColorEnd(QColor bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        this->update();
    }
}

void LSignalColumn::setBarBgColor(QColor barBgColor)
{
    if (this->barBgColor != barBgColor) {
        this->barBgColor = barBgColor;
        this->update();
    }
}

void LSignalColumn::setBarColorStart(QColor barColorStart)
{
    if (this->barColorStart != barColorStart) {
        this->barColorStart = barColorStart;
        this->update();
    }
}

void LSignalColumn::setBarColorMid(QColor barColorMid)
{
    if (this->barColorMid != barColorMid) {
        this->barColorMid = barColorMid;
        this->update();
    }
}

void LSignalColumn::setBarColorEnd(QColor barColorEnd)
{
    if (this->barColorEnd != barColorEnd) {
        this->barColorEnd = barColorEnd;
        this->update();
    }
}

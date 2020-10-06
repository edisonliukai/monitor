#pragma execution_character_set("utf-8")

#include "LSmoothWaveform.h"

#include "qpainter.h"
#include "qpainterpath.h"
#include "qdebug.h"
#include<QTimer>
QPainterPath LSmoothCurveCreator::createSmoothCurve(const QVector<QPointF> &points)
{
    QPainterPath path;
    int len = points.size();
    if (len < 2) {
        return path;
    }

    QVector<QPointF> firstControlPoints;
    QVector<QPointF> secondControlPoints;
    calculateControlPoints(points, &firstControlPoints, &secondControlPoints);
    path.moveTo(points[0].x(), points[0].y());

    for (int i = 0; i < len - 1; ++i) {
        path.cubicTo(firstControlPoints[i], secondControlPoints[i], points[i + 1]);
    }

    return path;
}

void LSmoothCurveCreator::calculateFirstControlPoints(double *&result, const double *rhs, int n)
{
    result = new double[n];
    double *tmp = new double[n];
    double b = 2.0;
    result[0] = rhs[0] / b;

    for (int i = 1; i < n; i++) {
        tmp[i] = 1 / b;
        b = (i < n - 1 ? 4.0 : 3.5) - tmp[i];
        result[i] = (rhs[i] - result[i - 1]) / b;
    }

    for (int i = 1; i < n; i++) {
        result[n - i - 1] -= tmp[n - i] * result[n - i];
    }

    delete tmp;
}

void LSmoothCurveCreator::calculateControlPoints(const QVector<QPointF> &knots, QVector<QPointF> *firstControlPoints, QVector<QPointF> *secondControlPoints)
{
    int n = knots.size() - 1;
    for (int i = 0; i < n; ++i) {
        firstControlPoints->append(QPointF());
        secondControlPoints->append(QPointF());
    }

    if (n == 1) {
        (*firstControlPoints)[0].rx() = (2 * knots[0].x() + knots[1].x()) / 3;
        (*firstControlPoints)[0].ry() = (2 * knots[0].y() + knots[1].y()) / 3;
        (*secondControlPoints)[0].rx() = 2 * (*firstControlPoints)[0].x() - knots[0].x();
        (*secondControlPoints)[0].ry() = 2 * (*firstControlPoints)[0].y() - knots[0].y();
        return;
    }

    double *xs = 0;
    double *ys = 0;
    double *rhsx = new double[n];
    double *rhsy = new double[n];

    for (int i = 1; i < n - 1; ++i) {
        rhsx[i] = 4 * knots[i].x() + 2 * knots[i + 1].x();
        rhsy[i] = 4 * knots[i].y() + 2 * knots[i + 1].y();
    }

    rhsx[0] = knots[0].x() + 2 * knots[1].x();
    rhsx[n - 1] = (8 * knots[n - 1].x() + knots[n].x()) / 2.0;
    rhsy[0] = knots[0].y() + 2 * knots[1].y();
    rhsy[n - 1] = (8 * knots[n - 1].y() + knots[n].y()) / 2.0;

    calculateFirstControlPoints(xs, rhsx, n);
    calculateFirstControlPoints(ys, rhsy, n);

    for (int i = 0; i < n; ++i) {
        (*firstControlPoints)[i].rx() = xs[i];
        (*firstControlPoints)[i].ry() = ys[i];

        if (i < n - 1) {
            (*secondControlPoints)[i].rx() = 2 * knots[i + 1].x() - xs[i + 1];
            (*secondControlPoints)[i].ry() = 2 * knots[i + 1].y() - ys[i + 1];
        } else {
            (*secondControlPoints)[i].rx() = (knots[n].x() + xs[n - 1]) / 2;
            (*secondControlPoints)[i].ry() = (knots[n].y() + ys[n - 1]) / 2;
        }
    }

    delete xs;
    delete ys;
    delete rhsx;
    delete rhsy;
}

LSmoothWaveform::LSmoothWaveform(QWidget *parent) : QWidget(parent)
  ,m_waveName(" ")
  ,m_timer(new QTimer(this))

{
    minValue = 0;
    maxValue = 100;
    xStep = 10;
    yStep = 10;

    space = 40;
    title = "曲线图";
    smooth = true;
    showHLine = false;
    showPoint = false;
    showPointBg = false;

    bgColorStart = QColor(79, 79, 79);
    bgColorEnd = QColor(51, 51, 51);
    textColor = QColor(250, 250, 250);
    pointColor = QColor(38, 114, 179);
    QVector<double> data;
    for (int i = 0; i < 100; i++) {
        int value = qrand() % 80;
        value = (value < 20 ? 20 : value);
        data.push_front(value);
    }

    //setData(data);
    m_timer->setInterval(200);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(addDataToWave()));
    //m_timer->start();;
    //setShowPoint(true);
}

LSmoothWaveform:: ~LSmoothWaveform()
{
    if(m_timer)
    {
        delete m_timer;
        m_timer  = NULL;
    }

}
void LSmoothWaveform::mousePressEvent(QMouseEvent *)
{
 QString name = getWaveName();

  if(name == "spo2A")
  {

      emit SigWaveWidgetClicked(0);
  }
  else if(name == "spo2B")
  {
      emit SigWaveWidgetClicked(1);
  }
  else if(name == "co2")
  {
      emit SigWaveWidgetClicked(2);
  }

}

void LSmoothWaveform::paintEvent(QPaintEvent *)
{

    //绘制准备工作,启用反锯齿
    QPainter painter(this);
    //painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing);
     painter.setRenderHints(QPainter::Antialiasing,true);
    //绘制背景
    //drawBg(&painter);
    //绘制盒子
    drawBox(&painter);
    //绘制文字
    //drawText(&painter);
    //绘制标题
    //drawTitle(&painter);
    //绘制数据点
    drawPoint(&painter);


}

void LSmoothWaveform::drawBg(QPainter *painter)
{
    painter->save();
    painter->setPen(Qt::NoPen);
    QLinearGradient topGradient(rect().topLeft(), rect().bottomLeft());
    topGradient.setColorAt(0.0, bgColorStart);
    topGradient.setColorAt(1.0, bgColorEnd);
    painter->setBrush(topGradient);
    painter->drawRect(rect());
    painter->restore();
}

void LSmoothWaveform::drawBox(QPainter *painter)
{
    painter->save();

    QPointF topLeftPot(space, space);
    QPointF bottomRightPot(width() - space / 4, height() - space / 4);
    painter->setPen(textColor);
    painter->setBrush(Qt::NoBrush);

    pointRect = QRectF(topLeftPot, bottomRightPot);
    //painter->drawRect(pointRect); // 繪製區域邊框線
    //painter->drawLine(0,this->width(),this->x(),this->y());
    //绘制横线
   /* if (showHLine) {
        QPen pen(textColor, 1, Qt::DotLine);
        painter->setPen(pen);

        int step = (maxValue - minValue) / xStep;
        double increment = (double)pointRect.height() / step;
        double startY = pointRect.topLeft().y();

        for (int i = 0; i < step - 1; i++) {
            startY += increment;
            QPointF leftPot(pointRect.topLeft().x(), startY);
            QPointF rightPot(pointRect.topRight().x(), startY);
            painter->drawLine(leftPot, rightPot);
        }
    }*/

    painter->restore();
}

void LSmoothWaveform::drawText(QPainter *painter)
{
    painter->save();

    painter->setPen(textColor);
    painter->setBrush(Qt::NoBrush);

    int step = (maxValue - minValue) / xStep;
    int value = maxValue;
    double increment = (double)pointRect.height() / step;
    double startY = pointRect.topLeft().y();
    QString strValue;

    for (int i = 0; i <= step; i++) {
        strValue = QString("%1").arg(value);
        double textWidth = fontMetrics().width(strValue);
        double textHeight = fontMetrics().height();
        QPointF textPot(pointRect.topLeft().x() - 5 - textWidth, startY + textHeight / 2);
        painter->drawText(textPot, strValue);
        value -= xStep;
        startY += increment;
    }

    painter->restore();
}

void LSmoothWaveform::drawTitle(QPainter *painter)
{
    painter->save();

    painter->setPen(textColor);
    painter->setBrush(Qt::NoBrush);

    double titleX = (double)width() / 2;
    double titleY = space;
    double textWidth = fontMetrics().width(title);
    double textHeight = fontMetrics().height();

    //标题加粗显示
    QFont titleFont;
    titleFont.setBold(true);
    titleFont.setPixelSize(13);
    painter->setFont(titleFont);

    QPointF textPot(titleX - textWidth / 2, titleY / 2 + textHeight / 2);
    painter->drawText(textPot, title);

    painter->restore();
}

void LSmoothWaveform::drawPoint(QPainter *painter)
{
     painter->save();

    double startX = pointRect.topRight().x();
    QVector<QPointF> points;

    if (showPointBg) {
        points.push_back(QPointF(startX, pointRect.bottomRight().y()));
    }

    for (int i = 0; i < listData.count(); i++) {
        QPointF dataPot(startX, pointRect.bottomRight().y() - (double)listData.at(i) * (pointRect.height() / (maxValue - minValue)));
        points.push_back(dataPot);
        startX -= yStep;
    }

    if (showPointBg) {
        points.push_back(QPointF(startX, pointRect.bottomRight().y()));
    }

    //如果只有两个数据点不需要处理
    if (showPointBg && points.count() <= 2) {
        painter->restore();
        return;
    }
    QPen pen;
    pen.setColor(pointColor);
    painter->setPen(pen);

    if (showPointBg) {
        painter->setBrush(QColor(pointColor.red(), pointColor.green(), pointColor.blue(), 150));
        if (!smooth) {
            painter->drawPolygon(QPolygonF(points));
        }
    } else {
        painter->setBrush(Qt::NoBrush);
        if (!smooth) {
            painter->drawPolyline(QPolygonF(points));
        }
    }

    //绘制平滑曲线
    if (smooth) {
        QPainterPath path = LSmoothCurveCreator::createSmoothCurve(points);
        painter->drawPath(path);
    }

    //绘制坐标点
    /*if (showPoint) {
        for (int i = 0; i < points.count(); i++) {
            QPointF dataPot = points.at(i);
            painter->setBrush(pointColor);
            painter->drawEllipse(dataPot, 3, 3);
        }
    }*/
    //painter->setPen(Qt::DashLine);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);

    painter->drawLine(0,this->height(),this->width(),this->height());
    painter->restore();
}

void LSmoothWaveform::updateData()
{
    int count = pointRect.width() / yStep;
   // qDebug()<<count<<endl;
    int i = listData.count() - count;

    if (i > 0) {
        listData.remove(count, i);
    }

    this->update();
}

void LSmoothWaveform::setWaveName(QString wavename)
{
    m_waveName = wavename;
}

QString LSmoothWaveform::getWaveName()
{
    if(m_waveName == " ")
    {
        return " ";
    }
    else
    {
        return m_waveName;
    }
}

double LSmoothWaveform::getMinValue() const
{
    return this->minValue;
}

double LSmoothWaveform::getMaxValue() const
{
    return this->maxValue;
}

double LSmoothWaveform::getXStep() const
{
    return this->xStep;
}

double LSmoothWaveform::getYStep() const
{
    return this->yStep;
}

double LSmoothWaveform::getSpace() const
{
    return this->space;
}

QString LSmoothWaveform::getTitle() const
{
    return this->title;
}

bool LSmoothWaveform::getSmooth() const
{
    return this->smooth;
}

bool LSmoothWaveform::getShowHLine() const
{
    return this->showHLine;
}

bool LSmoothWaveform::getShowPoint() const
{
    return this->showPoint;
}

bool LSmoothWaveform::getShowPointBg() const
{
    return this->showPointBg;
}

QColor LSmoothWaveform::getBgColorStart() const
{
    return this->bgColorStart;
}

QColor LSmoothWaveform::getBgColorEnd() const
{
    return this->bgColorEnd;
}

QColor LSmoothWaveform::getTextColor() const
{
    return this->textColor;
}

QColor LSmoothWaveform::getPointColor() const
{
    return this->pointColor;
}

QSize LSmoothWaveform::sizeHint() const
{
    return QSize(500, 300);
}

QSize LSmoothWaveform::minimumSizeHint() const
{
    return QSize(200, 70);
}

void LSmoothWaveform::addData(double data)
{
    listData.push_front(data);
    updateData();
}

void LSmoothWaveform::setData(QVector<double> data)
{
    listData = data;
    updateData();
}

void LSmoothWaveform::clearData()
{
    listData.clear();
    this->update();
}

void LSmoothWaveform::addDataToWave()
{
    int value1 = qrand() % 130;
    value1 = (value1 < 20 ? 20 : value1);
    addData(value1);

    //int value2 = qrand() % 80;
    //value2 = (value2 < 20 ? 20 : value2);
    //ui->waveChart2->addData(value2);
}

void LSmoothWaveform::startDrawWave()
{
     if(m_timer)
     {
         m_timer->start();
     }
}

void LSmoothWaveform::setMinValue(double minValue)
{
    if (this->minValue != minValue) {
        this->minValue = minValue;
        this->update();
    }
}

void LSmoothWaveform::setMaxValue(double maxValue)
{
    if (this->maxValue != maxValue) {
        this->maxValue = maxValue;
        this->update();
    }
}

void LSmoothWaveform::setXStep(double xStep)
{
    if (this->xStep != xStep) {
        this->xStep = xStep;
        this->update();
    }
}

void LSmoothWaveform::setYStep(double yStep)
{
    if (this->yStep != yStep) {
        this->yStep = yStep;
        this->update();
    }
}

void LSmoothWaveform::setSpace(double space)
{
    if (this->space != space) {
        this->space = space;
        this->update();
    }
}

void LSmoothWaveform::setTitle(const QString &title)
{
    if (this->title != title) {
        this->title = title;
        this->update();
    }
}

void LSmoothWaveform::setSmooth(bool smooth)
{
    if (this->smooth != smooth) {
        this->smooth = smooth;
        this->update();
    }
}

void LSmoothWaveform::setShowHLine(bool showHLine)
{
    if (this->showHLine != showHLine) {
        this->showHLine = showHLine;
        this->update();
    }
}

void LSmoothWaveform::setShowPoint(bool showPoint)
{
    if (this->showPoint != showPoint) {
        this->showPoint = showPoint;
        this->update();
    }
}

void LSmoothWaveform::setShowPointBg(bool showPointBg)
{
    if (this->showPointBg != showPointBg) {
        this->showPointBg = showPointBg;
        this->update();
    }
}

void LSmoothWaveform::setBgColorStart(const QColor &bgColorStart)
{
    if (this->bgColorStart != bgColorStart) {
        this->bgColorStart = bgColorStart;
        this->update();
    }
}

void LSmoothWaveform::setBgColorEnd(const QColor &bgColorEnd)
{
    if (this->bgColorEnd != bgColorEnd) {
        this->bgColorEnd = bgColorEnd;
        this->update();
    }
}

void LSmoothWaveform::setTextColor(const QColor &textColor)
{
    if (this->textColor != textColor) {
        this->textColor = textColor;
        this->update();
    }
}

void LSmoothWaveform::setPointColor(const QColor &pointColor)
{
    if (this->pointColor != pointColor) {
        this->pointColor = pointColor;
        this->update();
    }
}


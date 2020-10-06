/************************************************************************************************
* program   :  Monitor                                                                          *
* autor     :  edison                                                                           *
* File Description : 软件公有窗体类                                                              *
* start date:  2020-8-27                                                                        *
*                                                                                               *
* **********************************************************************************************/
#pragma once
#include <QObject>
#include <QWidget>
#include<QLabel>
class LAppWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LAppWidget(QWidget *parent = nullptr);

signals:

public slots:
};

/*在指定的窗体区间绘制文本，让文本能够自适应窗体，而且随分辨率放大或者缩小*/
class LDrawTextWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LDrawTextWidget(QWidget *parent = nullptr);


public:
    void paintEvent(QPaintEvent *);

    void setStringText(QString string);
signals:

public slots:
private:
    QRectF m_rect;
    QString m_string;
    double    m_pix;
    bool   m_isflush;
};

/*在指定Label上绘制文本，让文本能够自适应窗体，而且随分辨率放大或者缩小*/
class LDrawTextLabel : public QLabel
{
    Q_OBJECT
public:
    explicit LDrawTextLabel(QWidget *parent = nullptr);


public:
    void paintEvent(QPaintEvent *);

    void setStringText(QString string);
signals:

public slots:
    void SlotSecEvent();
private:
    QTimer *m_timer;
    QRectF m_rect;
    QString m_string;
    double    m_pix;
     bool   m_isflush;

};



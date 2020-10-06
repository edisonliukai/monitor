/************************************************************************************************
* program   :  Monitor                                                                          *
* autor     :  edison                                                                           *
* File Description : 绘制压缩波形，主要是CCHD画波形                                                 *
* start date:  2020-8-23                                                                        *
*                                                                                               *
* **********************************************************************************************/
#pragma once
#include <QWidget>
#include<vector>
#include<QPainterPath>
#include"LAppCommom.h"
class CompressedWave : public QWidget
{
    Q_OBJECT

public:
    explicit CompressedWave(QWidget *parent = 0);
    ~CompressedWave();
public:
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent*);
    void setWaveColor(QColor color);
    void drawGird(QPainter&painter);
    void setPointData();
    void setDataLen(int data);
    void clearPointData();
    void createQpainterPath();
    void setDrawWaveDirection(DRAW_WAVE_DIRCTION direction);
    void ifStartDrawWave(bool flag);
    void ifDrawGird(bool flag);
public slots:
    void SlotSetData();
    void SlotUpdate();
private:
    bool m_ifDrawWave;
    bool m_ifDrawGird;
    std::vector<QPoint>m_pointList;
    QPainterPath *m_path;
    QTimer *m_timer;
    int m_num;
    int m_dataLen;
    DRAW_WAVE_DIRCTION  m_drawWaveDirction;
    QColor m_waveColor;

};

namespace Ui {
class LDrawCompressedWavefrom;
}

class LDrawCompressedWavefrom : public QWidget
{
    Q_OBJECT

public:
    explicit LDrawCompressedWavefrom(QWidget *parent = 0);
    ~LDrawCompressedWavefrom();
public:
    void resizeEvent(QResizeEvent*);

    void setWaveData(bool flag);
    void ifStartDrawWave(bool flag);
    void setDirection(DRAW_WAVE_DIRCTION direction);
    void setIfDrawGird(bool flag);
private:
    Ui::LDrawCompressedWavefrom *ui;
};



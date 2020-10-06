#ifndef LVALUETEXT_H
#define LVALUETEXT_H

#include <QObject>
#include <QWidget>
#include<QLabel>
class LValueText : public QWidget
{
    Q_OBJECT
public:
    explicit LValueText(QWidget *parent = nullptr);
    ~LValueText();
public:


    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent*);
    void setText(QString  string);
signals:

public slots:
    void SlotSetValue();
public:
    QTimer *m_timer;
    int m_value;
    QString m_text;
    QRectF  m_rectF;
};

#endif // LVALUETEXT_H

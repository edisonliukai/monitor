#ifndef LMONITORAPP_H
#define LMONITORAPP_H

#include <QWidget>

namespace Ui {
class LMonitorApp;
}

class LMonitorApp : public QWidget
{
    Q_OBJECT

public:
    explicit LMonitorApp(QWidget *parent = 0);
    ~LMonitorApp();
public slots:
    void appProc();
private:
    Ui::LMonitorApp *ui;
    QTimer  *m_timer;
};

#endif // LMONITORAPP_H

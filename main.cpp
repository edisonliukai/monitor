#include "LMonitor.h"
#include"LStartAnimation.h"
#include"LMonitorApp.h"
#include <QApplication>
#include<QPropertyAnimation>
#include<QFile>
class GetLMonitorQss
{
 public:
    static void setQss(const QString & qss)
    {
       QFile LMonitorQss(qss);
       LMonitorQss.open(QFile::ReadOnly);
       qApp->setStyleSheet(LMonitorQss.readAll());
       LMonitorQss.close();
    }
};
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    GetLMonitorQss::setQss(":/LMonitorQss.qss");
    //LMonitor lmonitor;
    LMonitorApp monitorapp;
    // 主界面設置淡入淡出效果
    QPropertyAnimation *animation = new QPropertyAnimation(&monitorapp,"windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    monitorapp.show();

    return a.exec();
}

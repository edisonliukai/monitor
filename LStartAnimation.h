#pragma once

#include <QWidget>
#include<QtNetwork>
#include<QNetworkReply>
namespace Ui {
class LStartAnimation;
}

class LStartAnimation : public QWidget
{
    Q_OBJECT

public:
    explicit LStartAnimation(QWidget *parent = 0);
    ~LStartAnimation();
public:
    void initPictrueUrl();
    void loadStartAimationPicture(const QString &szUrl);
    QString getUrl();
private:
    Ui::LStartAnimation *ui;
    QString   m_url;

};



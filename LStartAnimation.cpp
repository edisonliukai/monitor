#include "LStartAnimation.h"
#include "ui_LStartAnimation.h"

LStartAnimation::LStartAnimation(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LStartAnimation)
{
    ui->setupUi(this);
    m_url = " ";
    //initPictrueUrl();
    loadStartAimationPicture("http://123.207.249.1/data/images/app.png");

}

LStartAnimation::~LStartAnimation()
{
    delete ui;
}

void LStartAnimation::initPictrueUrl()
{
    QString urlArray[1] = {
      ":/foot.png",

    };
    //int i = qrand()%8;
    //m_url = urlArray[i];

}

void LStartAnimation::loadStartAimationPicture(const QString &szUrl)
{

            QUrl url(szUrl);
            QNetworkAccessManager manager;
            QEventLoop loop;

           // qDebug() << "Reading picture form " <<url;
            QNetworkReply *reply = manager.get(QNetworkRequest(url));
            if(!reply)
            {
                return;
            }
            //请求结束并下载完成后，退出子事件循环
            QObject::connect(reply, SIGNAL(finished()), &loop, SLOT(quit()));
            //开启子事件循环
            loop.exec();

            QByteArray jpegData = reply->readAll();
            QPixmap pixmap;
            pixmap.loadFromData(jpegData);
            ui->label->setScaledContents(true);
            ui->label->setPixmap(pixmap);
}

QString LStartAnimation::getUrl()
{
    if(m_url == " ")
    {
        return " ";
    }
    else
    {
        return m_url;
    }
}

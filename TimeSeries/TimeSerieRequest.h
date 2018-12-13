#ifndef TIMESERIEREQUEST_H
#define TIMESERIEREQUEST_H
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <iostream>
#include <QDebug>
#include <QCoreApplication>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>
#include <QStringList>
#include <QDebug>
#include <QMessageBox>
using namespace std;

/**
 * @brief Sending web request and process response from the Alphavantage API
 */
class TimeSerieRequest : public QObject
{
    Q_OBJECT

public:
    explicit TimeSerieRequest()
        : QObject(nullptr)
    {
        manager = new QNetworkAccessManager(this);
        connect(manager, SIGNAL(finished(QNetworkReply*)),
                this, SLOT(replyFinished(QNetworkReply*)));

    }

    void SendRequest(QString subURL)
    {
        QUrl url("https://www.alphavantage.co/query?"+subURL+"&apikey=1K3QJ3N3YWZQAEG2");

        QNetworkRequest request;
        request.setSslConfiguration(QSslConfiguration::defaultConfiguration());
        request.setUrl(url);
        QNetworkReply *reply = manager->get(request);
        connect(reply, SIGNAL(error(QNetworkReply::NetworkError)),
                this, SLOT(slotError(QNetworkReply::NetworkError)));
        connect(reply, SIGNAL(sslErrors(QList<QSslError>)),
                this, SLOT(slotSslErrors(QList<QSslError>)));
    }
    QMessageBox msgBox;

public:
signals:
    void QueryFinished(QByteArray a);

public slots:
    void replyFinished(QNetworkReply* reply)
    {
        QByteArray answer = reply->readAll();
        if(!answer.isNull())
            emit QueryFinished(answer);
    }
    void slotError(QNetworkReply::NetworkError)
    {
        msgBox.setText("Communication Error !");
        msgBox.exec();
    }

    void slotSslErrors(QList<QSslError>)
    {
        msgBox.setText("SSL error");
        msgBox.exec();
    }
private:
    QNetworkAccessManager *manager = nullptr;
};
#endif // TIMESERIEREQUEST_H

#ifndef LOADDATA_H
#define LOADDATA_H
#include <QObject>
#include <QString>
#include <QList>
#include <QVariant>
#include "TimeSerieRequest.h"

class LoadData : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString stockSymbol READ stockSymbol WRITE setStockSymbol NOTIFY stockSymbolChanged)
    Q_PROPERTY(QString forexFromSymbol READ forexFromSymbol WRITE setForexFromSymbol NOTIFY forexFromSymbolChanged)
    Q_PROPERTY(QString forexToSymbol READ forexToSymbol WRITE setForexToSymbol NOTIFY forexToSymbolChanged)
    Q_PROPERTY(QString cryptoSymbol READ cryptoSymbol WRITE setCryptoSymbol NOTIFY cryptoSymbolChanged)
    Q_PROPERTY(QString cryptoMarket READ cryptoMarket WRITE setCryptoMarket NOTIFY cryptoMarketChanged)
    Q_PROPERTY(QString stockPeriod READ stockPeriod WRITE setStockPeriod NOTIFY stockPeriodChanged)
    Q_PROPERTY(QString forexPeriod READ forexPeriod WRITE setForexPeriod NOTIFY forexPeriodChanged)
    Q_PROPERTY(QString cryptoPeriod READ cryptoPeriod WRITE setCryptoPeriod NOTIFY cryptoPeriodChanged)

public:
    explicit LoadData(QObject *parent = nullptr);

    /*Stock symbol getter and setter*/
    QString stockSymbol();
    void setStockSymbol(const QString &st_symb);

    /*Forex from symbol getter and setter*/
    QString forexFromSymbol();
    void setForexFromSymbol(const QString &fx_from_symb);

    /*Forex to symbol getter and setter*/
    QString forexToSymbol();
    void setForexToSymbol(const QString &fx_to_symb);

    /*Crypto symbol getter and setter*/
    QString cryptoSymbol();
    void setCryptoSymbol(const QString &crypto_symb);

    /*Crypto Market getter and setter*/
    QString cryptoMarket();
    void setCryptoMarket(const QString &crypto_market);

    /*Stock period getter and setter*/
    QString stockPeriod();
    void setStockPeriod(const QString &stock_period);

    /*Forex period getter and setter*/
    QString forexPeriod();
    void setForexPeriod(const QString &forex_period);

    /*Crypto period getter and setter*/
    QString cryptoPeriod();
    void setCryptoPeriod(const QString &crypto_period);

    /*Stock Data getter and setter*/
    QByteArray getStockData();
    void setStockData(const QByteArray &st_data);

    /*Forex data getter and setter*/
    QByteArray getForexData();
    void setForexData(const QByteArray &fx_data);

    /*Crypto data getter and setter*/
    QByteArray getCryptoData();
    void setCryptoData(const QByteArray &crypto_data);


    void Stock_Data_Processing();
    void Forex_Data_Processing();
    void Crypto_Data_Processing();
    TimeSerieRequest *request = new TimeSerieRequest();
    QMessageBox msgBox;

signals:
    void stockSymbolChanged();
    void forexFromSymbolChanged();
    void forexToSymbolChanged();
    void cryptoSymbolChanged();
    void cryptoMarketChanged();
    void stockPeriodChanged();
    void forexPeriodChanged();
    void cryptoPeriodChanged();
    void stockValueUpdated(QVariant len,QVariant min,QVariant max,QVariant min_Date,QVariant max_Date,QVariant i,QVariant o,QVariant h,QVariant l,QVariant c);
    void forexValueUpdated(QVariant fxlen,QVariant fxmin,QVariant fxmax,QVariant fxmin_Date,QVariant fxmax_Date,QVariant fxi,QVariant fxo,QVariant fxh,QVariant fxl,QVariant fxc);
    void cryptoValueUpdated(QVariant crlen,QVariant crmin,QVariant crmax,QVariant crmin_Date,QVariant crmax_Date,QVariant cri,QVariant cro,QVariant crh,QVariant crl,QVariant crc);
    void clearChart();
    void clearForexChart();
    void clearCryptoChart();
public slots:
    void buttonShowStockClicked();
    void buttonSaveStockClicked();
    void buttonShowForexClicked();
    void buttonSaveForexClicked();
    void buttonShowCryptoClicked();
    void buttonSaveCryptoClicked();
    void showData(QByteArray a);

private:
    QString m_stockSymbol;
    QString m_forexFromSymbol;
    QString m_forexToSymbol;
    QString m_cryptoSymbol;
    QString m_cryptoMarket;
    QString m_stock_period = "DAILY";
    QString m_forex_period = "DAILY" ;
    QString m_crypto_period = "DAILY";
    QByteArray m_request_answer;
    QByteArray m_stockData;
    QByteArray m_forexData;
    QByteArray m_cryptoData;
    QString m_index;

};




#endif // LOADDATA_H


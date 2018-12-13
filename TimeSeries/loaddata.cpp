#include "loaddata.h"

#include <QDebug>
#include "TimeSerieRequest.h"
#include <QMessageBox>
#include <QStandardPaths>
#include <QFileInfo>
#include <QFileDialog>

LoadData::LoadData(QObject *parent) :
    QObject(parent)
{
    connect(request,SIGNAL(QueryFinished(QByteArray)),this,SLOT(showData(QByteArray)));

}

QString LoadData::stockSymbol()
{
    return m_stockSymbol.toUpper();
}
void LoadData::setStockSymbol(const QString &st_symb)
{
    if (st_symb.compare(m_stockSymbol,Qt::CaseInsensitive)==0)
        return;
    m_stockSymbol = st_symb;
    emit stockSymbolChanged();
}
QString LoadData::forexFromSymbol()
{
    return m_forexFromSymbol.toUpper();
}
void LoadData::setForexFromSymbol(const QString &fx_from_symb)
{

    if (fx_from_symb.compare(m_forexFromSymbol,Qt::CaseInsensitive)==0)
        return;

    m_forexFromSymbol = fx_from_symb;
    emit forexFromSymbolChanged();
}
QString LoadData::forexToSymbol()
{
    return m_forexToSymbol.toUpper();
}
void LoadData::setForexToSymbol(const QString &fx_to_symb)
{

    if (fx_to_symb.compare(m_forexToSymbol,Qt::CaseInsensitive)==0)
        return;

    m_forexToSymbol = fx_to_symb;
    emit forexToSymbolChanged();
}
QString LoadData::cryptoSymbol()
{
    return m_cryptoSymbol.toUpper();
}
void LoadData::setCryptoSymbol(const QString &crypto_symb)
{

    if (crypto_symb.compare(m_cryptoSymbol,Qt::CaseInsensitive)==0)
        return;

    m_cryptoSymbol = crypto_symb;
    emit cryptoSymbolChanged();
}
QString LoadData::cryptoMarket()
{
    return m_cryptoMarket.toUpper();
}
void LoadData::setCryptoMarket(const QString &crypto_market)
{

    if (crypto_market.compare(m_cryptoMarket,Qt::CaseInsensitive)==0)
        return;

    m_cryptoMarket = crypto_market;
    emit cryptoMarketChanged();
}
QString LoadData::stockPeriod()
{
    return m_stock_period;
}
void LoadData::setStockPeriod(const QString &stockP)
{

    if (stockP == m_stock_period)
        return;

    m_stock_period = stockP;
    emit stockPeriodChanged();
}
QString LoadData::forexPeriod()
{
    return m_forex_period;
}
void LoadData::setForexPeriod(const QString &forexP)
{

    if (forexP == m_forex_period)
        return;

    m_forex_period = forexP;
    emit forexPeriodChanged();
}
QString LoadData::cryptoPeriod()
{
    return m_crypto_period;
}
void LoadData::setCryptoPeriod(const QString &cryptoP)
{

    if (cryptoP == m_crypto_period)
        return;

    m_crypto_period = cryptoP;
    emit cryptoPeriodChanged();
}

QByteArray LoadData::getStockData()
{
    return m_stockData;
}
void LoadData::setStockData(const QByteArray &st_data)
{
    m_stockData = st_data;
}
QByteArray LoadData::getForexData()
{
    return m_forexData;
}
void LoadData::setForexData(const QByteArray &fx_data)
{
    m_forexData = fx_data;
}
QByteArray LoadData::getCryptoData()
{
    return m_cryptoData;
}
void LoadData::setCryptoData(const QByteArray &crypto_data)
{
    m_cryptoData = crypto_data;
}

void LoadData::buttonShowStockClicked()
{
    QString url = "function=TIME_SERIES_"+stockPeriod()+"&symbol="+stockSymbol();

    if(stockSymbol().isEmpty())
    {
        msgBox.setText("Please enter a symbol(Like MSFT)");
        msgBox.exec();
    }
    else
    {
       request->SendRequest(url);
    }


}
void LoadData::buttonSaveStockClicked()
{
    QString filename = "Stock_Data.json";
    if(getStockData().isNull()) {
        msgBox.setText("There is no data to save!");
        msgBox.exec();
    }
    else{
        QFile file(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+"\\"+filename);
        QFileInfo f(file);
        if (!file.open(QIODevice::WriteOnly)) {
            msgBox.setText("Failed to open file"+file.errorString());
            msgBox.exec();
        }
        else{
            file.write(getStockData());
            file.close();
            msgBox.setText("File saved in"+f.absoluteFilePath());
            msgBox.exec();
            }
        }
}
void LoadData::buttonShowForexClicked(){
    QString url = "function=FX_"+forexPeriod()+"&from_symbol="+forexFromSymbol()+"&to_symbol="+forexToSymbol();
    if(forexFromSymbol().isEmpty() || forexToSymbol().isEmpty())
    {
        msgBox.setText("Please enter a symbol(Like MSFT)");
        msgBox.exec();
    }
    else
    {
       request->SendRequest(url);
    }
}
void LoadData::buttonSaveForexClicked(){
    QString filename = "Forex_Data.json";
    if(getForexData().isNull()) {
        msgBox.setText("There is no data to save!");
        msgBox.exec();
    }
    else{
        QFile file(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+"\\"+filename);
        QFileInfo f(file);
        if (!file.open(QIODevice::WriteOnly)) {
            msgBox.setText("Failed to open file"+file.errorString());
            msgBox.exec();
        }
        else{
            file.write(getForexData());
            file.close();
            msgBox.setText("File saved in"+f.absoluteFilePath());
            msgBox.exec();
            }
    }
}
void LoadData::buttonShowCryptoClicked(){
    QString url = "function=DIGITAL_CURRENCY_"+cryptoPeriod()+"&symbol="+cryptoSymbol()+"&market="+cryptoMarket();
    if(cryptoSymbol().isEmpty() || cryptoMarket().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setText("Symbol and Market fields are mandatory for the request!");
        msgBox.exec();
    }
    else
    {
       request->SendRequest(url);
    }

}
void LoadData::buttonSaveCryptoClicked(){
    QString filename = "Crypto_Data.json";
    if(getCryptoData().isNull()) {
        msgBox.setText("There is no data to save!");
        msgBox.exec();
    }
    else{
        QFile file(QStandardPaths::writableLocation(QStandardPaths::DesktopLocation)+"\\"+filename);
        QFileInfo f(file);
        if (!file.open(QIODevice::WriteOnly)) {
            msgBox.setText("Failed to open file"+file.errorString());
            msgBox.exec();
        }
        else{
            file.write(getCryptoData());
            file.close();
            msgBox.setText("File saved in"+f.absoluteFilePath());
            msgBox.exec();
            }
        }
}
void LoadData::Stock_Data_Processing(){

    QJsonDocument json = QJsonDocument::fromJson(getStockData());
    QJsonObject rootElement = json.object();
    QStringList kk = rootElement.keys();
    QJsonObject timeSeries = rootElement[kk.at(1)].toObject();
    QStringList keys = timeSeries.keys();
    QStringList tmpKeys;
    QJsonObject timeserieObj;
    double min = timeSeries.value(keys.at(0)).toObject().value(timeSeries.value(keys.at(0)).toObject().keys().at(2)).toString().toDouble();
    double max = timeSeries.value(keys.at(0)).toObject().value(timeSeries.value(keys.at(0)).toObject().keys().at(1)).toString().toDouble();
    QString min_Date = keys.at(0);
    QString max_Date = keys.at(keys.length()-1);
    int counter = 0;
    for(const QJsonValue& timeserie : timeSeries)
    {
        timeserieObj = timeserie.toObject();
        tmpKeys = timeserieObj.keys();

        min = qMin(min,timeserieObj[tmpKeys.at(2)].toString().toDouble());
        max = qMax(max,timeserieObj[tmpKeys.at(1)].toString().toDouble());
        emit stockValueUpdated(QVariant(keys.length()),QVariant(min),QVariant(max),QVariant(min_Date),QVariant(max_Date),
                          QVariant(keys.at(counter)),QVariant(timeserieObj[tmpKeys.at(0)].toString().toDouble()),
                QVariant(timeserieObj[tmpKeys.at(1)].toString().toDouble()),
                QVariant(timeserieObj[tmpKeys.at(2)].toString().toDouble()),
                QVariant(timeserieObj[tmpKeys.at(3)].toString().toDouble()));
        counter++;
    }

}
void LoadData::Forex_Data_Processing(){
    QJsonDocument json = QJsonDocument::fromJson(getForexData());
    QJsonObject rootElement = json.object();
    QStringList kk = rootElement.keys();
    QJsonObject timeSeries = rootElement[kk.at(1)].toObject();
    QStringList keys = timeSeries.keys();
    QStringList tmpKeys;
    QJsonObject timeserieObj;
    double min = timeSeries.value(keys.at(0)).toObject().value(timeSeries.value(keys.at(0)).toObject().keys().at(2)).toString().toDouble();
    double max = timeSeries.value(keys.at(0)).toObject().value(timeSeries.value(keys.at(0)).toObject().keys().at(1)).toString().toDouble();
    QString min_Date = keys.at(0);
    QString max_Date = keys.at(keys.length()-1);
    int counter = 0;
    for(const QJsonValue& timeserie : timeSeries)
    {
        timeserieObj = timeserie.toObject();
        tmpKeys = timeserieObj.keys();

        min = qMin(min,timeserieObj[tmpKeys.at(2)].toString().toDouble());
        max = qMax(max,timeserieObj[tmpKeys.at(1)].toString().toDouble());
        emit forexValueUpdated(QVariant(keys.length()),QVariant(min),QVariant(max),QVariant(min_Date),QVariant(max_Date),
                          QVariant(keys.at(counter)),QVariant(timeserieObj[tmpKeys.at(0)].toString().toDouble()),
                QVariant(timeserieObj[tmpKeys.at(1)].toString().toDouble()),
                QVariant(timeserieObj[tmpKeys.at(2)].toString().toDouble()),
                QVariant(timeserieObj[tmpKeys.at(3)].toString().toDouble()));
        counter++;
    }
}
void LoadData::Crypto_Data_Processing(){
    QJsonDocument json = QJsonDocument::fromJson(getCryptoData());
    QJsonObject rootElement = json.object();
    QStringList kk = rootElement.keys();
    QJsonObject timeSeries = rootElement[kk.at(1)].toObject();
    QStringList keys = timeSeries.keys();
    QStringList tmpKeys;
    QJsonObject timeserieObj;
    double min = timeSeries.value(keys.at(0)).toObject().value(timeSeries.value(keys.at(0)).toObject().keys().at(4)).toString().toDouble();
    double max = timeSeries.value(keys.at(0)).toObject().value(timeSeries.value(keys.at(0)).toObject().keys().at(2)).toString().toDouble();
    QString min_Date = keys.at(0);
    QString max_Date = keys.at(keys.length()-1);
    int counter = 0;
    for(const QJsonValue& timeserie : timeSeries)
    {
        timeserieObj = timeserie.toObject();
        tmpKeys = timeserieObj.keys();

        min = qMin(min,timeserieObj[tmpKeys.at(4)].toString().toDouble());
        max = qMax(max,timeserieObj[tmpKeys.at(2)].toString().toDouble());
        emit cryptoValueUpdated(QVariant(keys.length()),QVariant(min),QVariant(max),QVariant(min_Date),QVariant(max_Date),
                          QVariant(keys.at(counter)),QVariant(timeserieObj[tmpKeys.at(0)].toString().toDouble()),
                QVariant(timeserieObj[tmpKeys.at(2)].toString().toDouble()),
                QVariant(timeserieObj[tmpKeys.at(4)].toString().toDouble()),
                QVariant(timeserieObj[tmpKeys.at(6)].toString().toDouble()));
        counter++;
    }
}

void LoadData::showData(QByteArray a)
{
    QJsonDocument json = QJsonDocument::fromJson(a);
    QJsonObject rootElement = json.object();
    QStringList keys = rootElement.keys();
    if(keys.at(0)=="Error Message")
    {
        msgBox.setText("Invalid parameter!");
        msgBox.exec();

    }
    else {
        if(keys.at(1).contains("Digital")){
            setCryptoData(a);
            emit clearCryptoChart();
            Crypto_Data_Processing();
        }
        else if(keys.at(1).contains("FX")){
            setForexData(a);
            emit clearForexChart();
            Forex_Data_Processing();
        }
        else {
            setStockData(a);
            emit clearChart();
            Stock_Data_Processing();
        }
    }

}




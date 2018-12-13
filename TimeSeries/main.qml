import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0
import io.qt.examples.loaddata 1.0
import QtCharts 2.2

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Time Series")
    LoadData {
        id: loaddata
        onClearChart: {
                openSerie.clear()
                highSerie.clear()
                lowSerie.clear()
                closeSerie.clear()
            }
        onClearForexChart: {
            forex_open_serie.clear()
            forex_close_serie.clear()
            forex_high_serie.clear()
            forex_low_serie.clear()
        }
        onClearCryptoChart: {
            crypto_open_serie.clear()
            crypto_close_serie.clear()
            crypto_high_serie.clear()
            crypto_low_serie.clear()
        }
        onStockValueUpdated:{
            var dat = i.split("-");
            var min_dat = min_Date.split("-");
            var max_dat = max_Date.split("-");
            yAxis.max = max
            yAxis.min = min
            xAxis.min= new Date(min_dat[0], min_dat[1]-1, min_dat[2])
            xAxis.max = new Date(max_dat[0], max_dat[1]-1, max_dat[2])
            openSerie.append(new Date(dat[0], dat[1]-1, dat[2]),o)
            highSerie.append(new Date(dat[0], dat[1]-1, dat[2]),h)
            lowSerie.append(new Date(dat[0], dat[1]-1, dat[2]),l)
            closeSerie.append(new Date(dat[0], dat[1]-1, dat[2]),c)

        }
        onForexValueUpdated: {
            var dat = fxi.split("-");
            var min_dat = fxmin_Date.split("-");
            var max_dat = fxmax_Date.split("-");
            yAxis1.max = fxmax
            yAxis1.min = fxmin
            xAxis1.min= new Date(min_dat[0], min_dat[1]-1, min_dat[2])
            xAxis1.max = new Date(max_dat[0], max_dat[1]-1, max_dat[2])
            forex_open_serie.append(new Date(dat[0], dat[1]-1, dat[2]),fxo)
            forex_high_serie.append(new Date(dat[0], dat[1]-1, dat[2]),fxh)
            forex_low_serie.append(new Date(dat[0], dat[1]-1, dat[2]),fxl)
            forex_close_serie.append(new Date(dat[0], dat[1]-1, dat[2]),fxc)
        }
        onCryptoValueUpdated: {
            var dat = cri.split("-");
            var min_dat = crmin_Date.split("-");
            var max_dat = crmax_Date.split("-");
            yAxis2.max = crmax
            yAxis2.min = crmin
            xAxis2.min= new Date(min_dat[0], min_dat[1]-1, min_dat[2])
            xAxis2.max = new Date(max_dat[0], max_dat[1]-1, max_dat[2])
            crypto_open_serie.append(new Date(dat[0], dat[1]-1, dat[2]),cro)
            crypto_high_serie.append(new Date(dat[0], dat[1]-1, dat[2]),crh)
            crypto_low_serie.append(new Date(dat[0], dat[1]-1, dat[2]),crl)
            crypto_close_serie.append(new Date(dat[0], dat[1]-1, dat[2]),crc)
        }
    }

    SwipeView {
        id: swipeView
        anchors.rightMargin: 0
        anchors.bottomMargin: 0
        anchors.leftMargin: 0
        anchors.topMargin: 0
        anchors.fill: parent
        currentIndex: tabBar.currentIndex

        Page {
            id: page
            Item {
                id: item1
                property alias textField3: textField3
                property alias button3: button3
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                ChartView {
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.right: stcolumnLayout.left
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.top: rowLayout1.bottom
                    anchors.topMargin: 10
                    antialiasing: true
                    DateTimeAxis {
                        format: "yyyy-MM-dd"
                        id: xAxis
                        min: new Date(2018,06,06)
                        max: new Date(Date.now())
                        tickCount: 7
                        titleText: "<font color='green'>Date [Year-Month-Day]</font>"
                    }

                    ValueAxis{
                        id: yAxis
                        min: 0
                        max: 150
                        titleText: "<font color='red'>Stock[USD]</font>"
                    }

                    LineSeries{
                        name: " Stock: Open"
                        id: openSerie
                        axisX: xAxis
                        axisY: yAxis

                    }

                    LineSeries{
                        name: " Stock: High"
                        id: highSerie
                        axisX: xAxis
                        axisY: yAxis
                    }
                    LineSeries{
                        name: " Stock: Low"
                        id: lowSerie
                        axisX: xAxis
                        axisY: yAxis
                    }
                    LineSeries{
                        name: " Stock: Close"
                        id: closeSerie
                        axisX: xAxis
                        axisY: yAxis
                    }
                }

                RowLayout {
                    x: 165
                    anchors.top: parent.top
                    anchors.topMargin: 15
                    id: rowLayout1
                    anchors.horizontalCenterOffset: 0
                    anchors.horizontalCenter: parent.horizontalCenter

                    TextField {
                        id: textField3
                        text: loaddata.stockSymbol
                        placeholderText: qsTr("Symbol(Ex: MSFT)")
                        onTextChanged: loaddata.stockSymbol = text
                    }

                    Button {
                        id: button3
                        text: qsTr("Show result")
                        onClicked: loaddata.buttonShowStockClicked()

                    }
                    Button {
                        id: buttonSaveStock
                        text: qsTr("Save result")
                        onClicked: loaddata.buttonSaveStockClicked()

                    }
                }

                ColumnLayout {
                    id: stcolumnLayout
                    x: 540
                    width: 100
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: rowLayout1.bottom
                    anchors.topMargin: 10

                    RadioButton {
                        id: stdailyRadioButton
                        text: qsTr("Daily")
                        checked: true
                        onClicked: loaddata.stockPeriod = "DAILY"
                    }

                    RadioButton {
                        id: stweeklyRadioButton
                        text: qsTr("Weekly")
                        onClicked: loaddata.stockPeriod = "WEEKLY"
                    }

                    RadioButton {
                        id: stmonthlyRadioButton
                        text: qsTr("Monthly")
                        onClicked: loaddata.stockPeriod = "MONTHLY"
                    }
                }

            }
        }
        Page {
            id: page1
            Item {
                id: item2
                property alias textField1_1: textField1_1
                property alias textField1_2: textField1_2
                property alias button1: button1
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                ChartView {
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.right: fxcolumnLayout.left
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.top: rowLayout2.bottom
                    anchors.topMargin: 10
                    antialiasing: true
                    DateTimeAxis {
                        format: "yyyy-MM-dd"
                        id: xAxis1
                        min: new Date(2018,06,06)
                        max: new Date(Date.now())
                        tickCount: 7
                        titleText: "<font color='green'>Date [Year-Month-Day]</font>"
                    }

                    ValueAxis{
                        id: yAxis1
                        min: 0
                        max: 150
                        titleText: "<font color='red'>FX</font>"
                    }

                    LineSeries{
                        name: "Fx: Open"
                        id: forex_open_serie
                        axisX: xAxis1
                        axisY: yAxis1
                    }
                    LineSeries{
                        name: "Fx: High"
                        id: forex_high_serie
                        axisX: xAxis1
                        axisY: yAxis1
                    }
                    LineSeries{
                        name: "Fx: Low"
                        id: forex_low_serie
                        axisX: xAxis1
                        axisY: yAxis1
                    }
                    LineSeries{
                        name: "Fx: Close"
                        id: forex_close_serie
                        axisX: xAxis1
                        axisY: yAxis1
                    }
                }


                RowLayout {
                    anchors.horizontalCenterOffset: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: 0
                    anchors.top: parent.top
                    id: rowLayout2

                    TextField {
                        id: textField1_1
                        placeholderText: qsTr("From(Symbol)")
                        text: loaddata.forexFromSymbol
                        onTextChanged: loaddata.forexFromSymbol = text
                    }
                    TextField {
                        id: textField1_2
                        placeholderText: qsTr("TO(Symbol)")
                        text: loaddata.forexToSymbol
                        onTextChanged: loaddata.forexToSymbol = text
                    }

                    Button {
                        id: button1
                        text: qsTr("Show result")
                        onClicked: loaddata.buttonShowForexClicked()
                    }
                    Button {
                        id: buttonSaveFX
                        text: qsTr("Save result")
                        onClicked: loaddata.buttonSaveForexClicked()
                    }
                }
                ColumnLayout {
                    id: fxcolumnLayout
                    x: 540
                    width: 100
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: rowLayout2.bottom
                    anchors.topMargin: 10

                    RadioButton {
                        id: fxdailyRadioButton
                        text: qsTr("Daily")
                        checked: true
                        onClicked: loaddata.forexPeriod = "DAILY"
                    }

                    RadioButton {
                        id: fxweeklyRadioButton
                        text: qsTr("Weekly")
                        onClicked: loaddata.forexPeriod = "WEEKLY"
                    }

                    RadioButton {
                        id: fxmonthlyRadioButton
                        text: qsTr("Monthly")
                        onClicked: loaddata.forexPeriod = "MONTHLY"
                    }
                }
            }
        }

        Page {
            id: page2
            Item {
                id: item3
                property alias textField2_1: textField2_1
                property alias textField2_2: textField2_2
                property alias button2: button2
                anchors.right: parent.right
                anchors.rightMargin: 0
                anchors.left: parent.left
                anchors.leftMargin: 0
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 0
                anchors.top: parent.top
                anchors.topMargin: 0
                ChartView {
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.right: crcolumnLayout.left
                    anchors.rightMargin: 0
                    anchors.left: parent.left
                    anchors.leftMargin: 0
                    anchors.top: rowLayout3.bottom
                    anchors.topMargin: 10
                    antialiasing: true
                    DateTimeAxis {
                        format: "yyyy-MM-dd"
                        id: xAxis2
                        min: new Date(2018,06,06)
                        max: new Date(Date.now())
                        tickCount: 7
                        titleText: "<font color='green'>Date [Year-Month-Day]</font>"
                    }

                    ValueAxis{
                        id: yAxis2
                        min: 0
                        max: 150
                        titleText: "<font color='red'>Value in the market</font>"
                    }

                    LineSeries{
                        name: "Crypto: Open"
                        id: crypto_open_serie
                        axisX: xAxis2
                        axisY: yAxis2
                    }
                    LineSeries{
                        name: "Crypto: High"
                        id: crypto_high_serie
                        axisX: xAxis2
                        axisY: yAxis2
                    }
                    LineSeries{
                        name: "Crypto: Low"
                        id: crypto_low_serie
                        axisX: xAxis2
                        axisY: yAxis2
                    }
                    LineSeries{
                        name: "Crypto: Close"
                        id: crypto_close_serie
                        axisX: xAxis2
                        axisY: yAxis2
                    }
                }

                RowLayout {
                    anchors.horizontalCenterOffset: 0
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.topMargin: 0
                    anchors.top: parent.top
                    id: rowLayout3

                    TextField {
                        id: textField2_1
                        placeholderText: qsTr("Symbol(Ex: BTC)")
                        text: loaddata.cryptoSymbol
                        onTextChanged: loaddata.cryptoSymbol = text
                    }
                    TextField {
                        id: textField2_2
                        placeholderText: qsTr("Market(Ex: CNY)")
                        text: loaddata.cryptoMarket
                        onTextChanged: loaddata.cryptoMarket = text
                    }

                    Button {
                        id: button2
                        text: qsTr("Show result")
                        onClicked: loaddata.buttonShowCryptoClicked()
                    }
                    Button {
                        id: buttonSaveCrypto
                        text: qsTr("Save result")
                        onClicked: loaddata.buttonSaveCryptoClicked()
                    }
                }
                ColumnLayout {
                    id: crcolumnLayout
                    x: 540
                    width: 100
                    anchors.right: parent.right
                    anchors.rightMargin: 0
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: 0
                    anchors.top: rowLayout3.bottom
                    anchors.topMargin: 10

                    RadioButton {
                        id: crdailyRadioButton
                        text: qsTr("Daily")
                        checked: true
                        onClicked: loaddata.cryptoPeriod = "DAILY"
                    }

                    RadioButton {
                        id: crweeklyRadioButton
                        text: qsTr("Weekly")
                        onClicked: loaddata.cryptoPeriod = "WEEKLY"
                    }

                    RadioButton {
                        id: crmonthlyRadioButton
                        text: qsTr("Monthly")
                        onClicked: loaddata.cryptoPeriod = "MONTHLY"
                    }
                }
            }
        }
    }
    footer: TabBar {
        id: tabBar
        currentIndex:{ swipeView.currentIndex
        }


        TabButton {
            text: qsTr("Stock")
        }
        TabButton {
            text: qsTr("Forex")
            clip: false
        }
        TabButton {
            text: qsTr("Cryptocurrencies")
        }
    }
}


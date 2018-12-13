#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QApplication>
#include <QQmlProperty>
#include <QQmlContext>
#include <QMetaObject>

#include <QObject>
#include "loaddata.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication app(argc, argv);
    qmlRegisterType<LoadData>("io.qt.examples.loaddata", 1, 0, "LoadData");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QLatin1String("qrc:/main.qml")));


    return app.exec();
}

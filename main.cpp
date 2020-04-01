#include <QWindow>
#include <QIcon>
#include <QFont>
#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "calculator.h"

int main(int argc, char *argv[]) {
    const QUrl url(QStringLiteral("qrc:/main.qml"));

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    app.setFont(QFont("Consolas"));
    app.setWindowIcon(QIcon(":images/calc-icon.png"));

    qmlRegisterType<Calculator>("calculator.calculator", 1, 0, "Calculator");

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    engine.load(url);

    return app.exec();
}

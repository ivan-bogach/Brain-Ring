#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include <controllers/master-controller.h>
#include <controllers/command-controller.h>
#include <data/stringdecorator.h>
#include <data/intdecorator.h>
#include <models/game.h>
#include <models/question.h>
#include <framework/command.h>

int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


// To be able to use a given class in QML
//registering	the	type	with	the	QML	engine
    qmlRegisterType<br::controllers::MasterController>("BR", 1, 0, "MasterController");
    qmlRegisterType<br::controllers::NavigationController>("BR", 1, 0, "NavigationController");
    qmlRegisterType<br::controllers::Commandcontroller>("BR", 1, 0, "Commandcontroller");
    qmlRegisterType<br::data::StringDecorator>("BR", 1, 0, "StringDecorator");
    qmlRegisterType<br::data::IntDecorator>("BR", 1, 0, "IntDecorator");
    qmlRegisterType<br::models::Game>("BR", 1, 0, "Game");
    qmlRegisterType<br::models::Question>("BR", 1, 0, "Question");
    qmlRegisterType<br::framework::Command>("BR", 1, 0, "Command");

// instantiate an instance of MasterController and inject it into the root QML context
    br::controllers::MasterController masterController;
    QQmlApplicationEngine engine;

    engine.addImportPath("qrc:/");
    engine.rootContext()->setContextProperty("masterController", &masterController);
    engine.load(QUrl(QStringLiteral("qrc:/views/MasterView.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

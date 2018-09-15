#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QtQml>

#include <controllers/master-controller.h>
#include <controllers/command-controller.h>
#include <controllers/navigation-controller.h>
#include <framework/command.h>

int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


// To be able to use a given class in QML
//registering	the	type	with	the	QML	engine
    qmlRegisterType<br::controllers::MasterController>("BR", 1, 1, "MasterController");
    qmlRegisterType<br::controllers::NavigationController>("BR", 1, 0, "NavigationController");
    qmlRegisterType<br::controllers::CommandController>("BR", 1, 0, "CommandController");
    qmlRegisterType<br::framework::Command>("BR", 1, 0, "Command");

// instantiate an instance of MasterController and inject it into the root QML context
    br::controllers::MasterController masterController;
    QQmlApplicationEngine engine;
// add the import path to qmldir definition file
    engine.addImportPath("qrc:/");
    engine.rootContext()->setContextProperty("masterController", &masterController);
    engine.load(QUrl(QStringLiteral("qrc:/views/MasterView.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

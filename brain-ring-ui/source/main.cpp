#include <QCoreApplication>
#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <controllers/master-controller.h>
#include <QQmlContext>
 #include <QtQml>

int main(int argc, char *argv[])
{
//    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);


// To be able to use a given class in QML
//registering	the	type	with	the	QML	engine
    qmlRegisterType<br::controllers::MasterController>("BR", 1, 1, "MasterController");
    qmlRegisterType<br::controllers::NavigationController>("BR", 1, 0, "NavigationController");

// instantiate an instance of MasterController and inject it into the root QML context
    br::controllers::MasterController masterController;
    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("masterController", &masterController);
    engine.load(QUrl(QStringLiteral("qrc:/views/MasterView.qml")));

    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}

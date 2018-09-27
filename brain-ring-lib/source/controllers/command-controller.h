#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <brain-ring-lib_global.h>
#include <controllers/i-database-controller.h>
#include <controllers/navigation-controller.h>
#include <models/game.h>
#include <framework/command.h>

namespace br {
namespace controllers {


class BRAINRINGLIBSHARED_EXPORT Commandcontroller : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QQmlListProperty<br::framework::Command> ui_createGameViewContextCommands READ ui_createGameViewContextCommands CONSTANT)

public:
    explicit Commandcontroller(QObject * _parent = nullptr, IDatabaseController* databaseController = nullptr, NavigationController* navigationController = nullptr, models::Game* newGame= nullptr);
    ~Commandcontroller();

    QQmlListProperty<br::framework::Command> ui_createGameViewContextCommands();

signals:

public slots:
    void onCreateGameSaveExecuted();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}
#endif // COMMANDCONTROLLER_H

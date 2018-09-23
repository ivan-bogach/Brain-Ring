#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <QtQml/QQmlListProperty>


#include <brain-ring-lib_global.h>
#include <framework/command.h>
#include <controllers/i-database-controller.h>
#include <controllers/navigation-controller.h>
#include <models/game.h>
#include <models/gamesearch.h>

namespace br {
namespace controllers {

class BRAINRINGLIBSHARED_EXPORT CommandController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<br::framework::Command> ui_createGameViewContextCommands READ ui_createGameViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<br::framework::Command> ui_findGameViewContextCommands READ ui_findGameViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty <br::framework::Command> ui_editGameViewContextCommands READ ui_editGameViewContextCommands CONSTANT)

public:
    explicit CommandController(QObject* _parent = nullptr, IDatabaseController* databaseController = nullptr, NavigationController* navigationController = nullptr, models::Game* newGame= nullptr, models::GameSearch* gameSearch = nullptr);
    ~CommandController();

//QQmlListProperty enables QML to interact with a list of custom objects
    QQmlListProperty<framework::Command> ui_createGameViewContextCommands();
    QQmlListProperty<framework::Command> ui_findGameViewContextCommands();
    QQmlListProperty<framework::Command> ui_editGameViewContextCommands();

signals:

public slots:
    void setSelectedGame(br::models::Game* game);

    void onCreateGameSaveExecuted();
    void onFindGameSearchExecuted();
    void onEditGameSaveExecuted();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}


#endif // COMMANDCONTROLLER_H

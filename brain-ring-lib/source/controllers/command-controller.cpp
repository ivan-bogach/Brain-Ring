#include "command-controller.h"

#include <QList>
#include <QDebug>

using namespace br::framework;
using namespace br::models;

namespace br {
namespace controllers {

class Commandcontroller::Implementation
{
public:
    Implementation(Commandcontroller* _commandController, IDatabaseController* _databaseController, NavigationController* _navigationController, Game* _newGame)
        : commandcontroller(_commandController)
        , databaseController(_databaseController)
        , navigationController(_navigationController)
        , newGame(_newGame)
    {
        Command* createGameSaveCommand = new Command(commandcontroller, QChar( 0xf0c7 ), "Сохранить");
        QObject::connect(createGameSaveCommand, &Command::executed, commandcontroller, &Commandcontroller::onCreateGameSaveExecuted);
        createGameViewContextCommands.append(createGameSaveCommand);
    }

    Commandcontroller* commandcontroller{nullptr};

    IDatabaseController* databaseController{nullptr};

    NavigationController* navigationController{nullptr};

    Game* newGame{nullptr};

    QList<Command*> createGameViewContextCommands{};
};

Commandcontroller::Commandcontroller(QObject *parent, IDatabaseController* databaseController, NavigationController* navigationController,  Game* newGame) : QObject(parent)
{
    implementation.reset(new Implementation(this, databaseController, navigationController, newGame));
}

Commandcontroller::~Commandcontroller() {}

QQmlListProperty<Command> Commandcontroller::ui_createGameViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->createGameViewContextCommands);
}

void Commandcontroller::onCreateGameSaveExecuted()
{
    qDebug() << "SAVE EXECUTED";
    implementation->databaseController->createRow(implementation->newGame->key(), implementation->newGame->id(), implementation->newGame->toJson());
    qDebug() << "New client saved.";
}

}
}

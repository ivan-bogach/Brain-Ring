#include "command-controller.h"

#include <QList>
#include <QDebug>

using namespace br::framework;
using namespace br::models;

namespace br {
namespace controllers {

class CommandController::Implementation
{
public:
    Implementation(CommandController* _commandController,IDatabaseController* _databaseController, Game* _newGame)
        : commandController(_commandController)
        , databaseController(_databaseController)
        , newGame(_newGame)
    {
        Command* createGameSaveCommand =  new Command(commandController, QChar( 0xf0c7 ), "Сохранить");

// connect	the	 executed() signal of the command to the onCreateGmaeSaveExecuted() slot of the CommandController
        QObject::connect(createGameSaveCommand, &Command::executed, commandController, &CommandController::onCreateGameSaveExecuted);
        createGameViewContextCommands.append(createGameSaveCommand);
    }

    CommandController* commandController{nullptr};

    IDatabaseController* databaseController{nullptr};
    Game* newGame{nullptr};

    QList<Command*> createGameViewContextCommands{};
};

CommandController::CommandController(QObject *parent, IDatabaseController* databaseController, Game* newGame)
    : QObject(parent)
{
    implementation.reset(new Implementation(this, databaseController, newGame));
}

CommandController::~CommandController(){}

QQmlListProperty<Command> CommandController::ui_createGameViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->createGameViewContextCommands);
}

void CommandController::onCreateGameSaveExecuted()
{
    qDebug() << "You executed the Save command!";

    implementation->databaseController->createRow(implementation->newGame->key(), implementation->newGame->id(), implementation->newGame->toJson());


    qDebug() << "New client saved.";
}

}
}

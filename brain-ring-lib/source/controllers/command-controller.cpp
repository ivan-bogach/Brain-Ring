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
    Implementation(CommandController* _commandController,IDatabaseController* _databaseController, NavigationController* _navigationController, Game* _newGame, GameSearch* _gameSearch)
        : commandController(_commandController)
        , databaseController(_databaseController)
        , navigationController(_navigationController)
        , newGame(_newGame)
        , gameSearch(_gameSearch)
    {
        Command* createGameSaveCommand =  new Command(commandController, QChar( 0xf0c7 ), "Сохранить");

// connect	the	 executed() signal of the command to the onCreateGmaeSaveExecuted() slot of the CommandController
        QObject::connect(createGameSaveCommand, &Command::executed, commandController, &CommandController::onCreateGameSaveExecuted);
        createGameViewContextCommands.append(createGameSaveCommand);

        Command* findGameSearchCommand = new Command(commandController, QChar( 0xf002 ), "Поиск");
        QObject::connect(findGameSearchCommand, &Command::executed, commandController, &CommandController::onFindGameSearchExecuted);
        findGameViewContextCommands.append(findGameSearchCommand);
    }

    CommandController* commandController{nullptr};

    IDatabaseController* databaseController{nullptr};

    NavigationController* navigationController{nullptr};

    Game* newGame{nullptr};

    GameSearch* gameSearch{nullptr};

    QList<Command*> createGameViewContextCommands{};

    QList<Command*> findGameViewContextCommands{};
};

CommandController::CommandController(QObject *parent, IDatabaseController* databaseController, NavigationController* navigationController ,Game* newGame, GameSearch* gameSearch)
    : QObject(parent)
{
    implementation.reset(new Implementation(this, databaseController, navigationController ,newGame, gameSearch));
}

CommandController::~CommandController(){}

QQmlListProperty<Command> CommandController::ui_createGameViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->createGameViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_findGameViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->findGameViewContextCommands);
}

void CommandController::onCreateGameSaveExecuted()
{
    qDebug() << "You executed the Save command!";

    implementation->databaseController->createRow(implementation->newGame->key(), implementation->newGame->id(), implementation->newGame->toJson());

    qDebug() << "New client saved.";
}

void CommandController::onFindGameSearchExecuted()
{
    qDebug() << "You executed the Search command";

    implementation->gameSearch->search();
}

}
}

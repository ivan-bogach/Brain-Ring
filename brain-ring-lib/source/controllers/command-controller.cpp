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
    Implementation(CommandController* _commandController,TCPController* _tcpController ,IDatabaseController* _databaseController, NavigationController* _navigationController, Game* _newGame, GameSearch* _gameSearch)
        : commandController(_commandController)
        , tcpController(_tcpController)
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

        Command* editGameSaveCommand = new Command(commandController, QChar( 0xf0c7), "Сохранить");
        QObject::connect(editGameSaveCommand, &Command::executed, commandController, &CommandController::onEditGameSaveExecuted);
        editGameViewContextCommands.append(editGameSaveCommand);

        Command* editGameDeleteCommand = new Command(commandController, QChar( 0xf0c7), "Удалить");
        QObject::connect(editGameDeleteCommand, &Command::executed, commandController, &CommandController::onEditGameDeleteExecuted);
        editGameViewContextCommands.append(editGameDeleteCommand);

        Command* startServerCommand = new Command(commandController, QChar(0xf0c7), "Старт");
        QObject::connect(startServerCommand, &Command::executed, commandController, &CommandController::onStartServerExecuted);
        gameViewContextCommands.append(startServerCommand);

//        Command* stopServerCommand = new Command(commandController, QChar(0xf0c7), "Стоп");
//        QObject::connect(stopServerCommand, &Command::executed, commandController, &CommandController::onStopServerExecuted);
//        gameViewContextCommands.append(stopServerCommand);
    }

    CommandController* commandController{nullptr};

    TCPController* tcpController{nullptr};

    IDatabaseController* databaseController{nullptr};

    NavigationController* navigationController{nullptr};

    Game* newGame{nullptr};

    GameSearch* gameSearch{nullptr};

    Game* selectedGame{nullptr};

    QList<Command*> createGameViewContextCommands{};

    QList<Command*> findGameViewContextCommands{};

    QList<Command*> editGameViewContextCommands{};

    QList<Command*> gameViewContextCommands{};
};

CommandController::CommandController(QObject *parent, TCPController* tcpController,IDatabaseController* databaseController, NavigationController* navigationController ,Game* newGame, GameSearch* gameSearch)
    : QObject(parent)
{
    implementation.reset(new Implementation(this, tcpController,databaseController, navigationController ,newGame, gameSearch));
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

QQmlListProperty<Command> CommandController::ui_editGameViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->editGameViewContextCommands);
}


QQmlListProperty<Command> CommandController::ui_gameViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->gameViewContextCommands);
}

void CommandController::onCreateGameSaveExecuted()
{
    qDebug() << "You executed the Save command!";

    implementation->databaseController->createRow(implementation->newGame->key(), implementation->newGame->id(), implementation->newGame->toJson());

//    implementation->gameSearch->searchText()->setValue("*");
//    implementation->gameSearch->searchText()->setValue(implementation->newGame->id());

//    implementation->gameSearch->search();
    implementation->gameSearch->searchAll();

//    implementation->navigationController->goFindGameView();

    qDebug() << "New client saved.";
}

void CommandController::onFindGameSearchExecuted()
{
    qDebug() << "You executed the Search command";

    implementation->gameSearch->search();
}

void CommandController::onEditGameSaveExecuted()
{
    qDebug() << "You executed Save command";

    implementation->databaseController->updateRow(implementation->selectedGame->key(), implementation->selectedGame->id(), implementation->selectedGame->toJson());

    qDebug() << "Udated game saved";
}

void CommandController::setSelectedGame(Game *game)
{
    implementation->selectedGame = game;
}

void CommandController::onEditGameDeleteExecuted()
{
    qDebug() << "You executed the Delete command!";

    implementation->databaseController->deleteRow(implementation->selectedGame->key(), implementation->selectedGame->id());
    implementation->selectedGame = nullptr;

    qDebug() << "Game Deleted";

    implementation->gameSearch->search();
    implementation->navigationController->goDashboardView();
}

void CommandController::onStartServerExecuted()
{
    qDebug() << "Command controller: You executed the Start command!";
    implementation->tcpController->startServer();
    qDebug() << "Command controller: server started!";
}

void CommandController::onStopServerExecuted()
{
    qDebug() << "Command controller: You executed the STOP command!";
    implementation->tcpController->stopServer();
    qDebug() << "Command controller: server stoped!";
}

}
}

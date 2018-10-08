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
    Implementation(CommandController* _commandController,
                   TCPController* _tcpController,
                   IDatabaseController* _databaseController,
                   NavigationController* _navigationController,
                   Game* _newGame,
                   Game* _selectedGame,
                   GameSearch* _gameSearch,
                   TCPClient* _tcpClient,
                   TCPClientsList* _tcpClientsList,
                   Settings* _settings
                   )
        : commandController(_commandController)
        , tcpController(_tcpController)
        , databaseController(_databaseController)
        , navigationController(_navigationController)
        , newGame(_newGame)
        , selectedGame(_selectedGame)
        , gameSearch(_gameSearch)
        , tcpClient(_tcpClient)
        , tcpClientsList(_tcpClientsList)
        , settings(_settings)
    {
        Command* createGameSaveCommand =  new Command(commandController, QChar( 0xf0c7 ), "Сохранить");
        QObject::connect(createGameSaveCommand, &Command::executed, commandController, &CommandController::onCreateGameSaveExecuted);
        addQuestionPanelContextCommands.append(createGameSaveCommand);


        Command* saveSettings = new Command(commandController, QChar( 0xf0c7 ), "Сохранить");
        QObject::connect(saveSettings, &Command::executed, commandController, &CommandController::onSaveSettingsExecuted);
        settingsViewContextCommands.append(saveSettings);

        Command* startServerCommand = new Command(commandController, QChar(0xf0c7), "Старт");
        QObject::connect(startServerCommand, &Command::executed, commandController, &CommandController::onStartServerExecuted);
        gameViewContextCommands.append(startServerCommand);

        for (int i = 0; i <= tcpController->SClients().size(); ++i)
        {
            QString str = QString::number(i);
            TCPClientCommand* tcpClientCommand = new TCPClientCommand(commandController, str, str + ".png");
            QObject::connect(tcpClientCommand, &TCPClientCommand::executed, commandController, &CommandController::onTCPClientExecuted);
            gameViewContextTCPClientCommands.append(tcpClientCommand);

        }


//        Command* stopServerCommand = new Command(commandController, QChar(0xf0c7), "Стоп");
//        QObject::connect(stopServerCommand, &Command::executed, commandController, &CommandController::onStopServerExecuted);
//        gameViewContextCommands.append(stopServerCommand);
    }

    CommandController* commandController{nullptr};

    TCPController* tcpController{nullptr};

    IDatabaseController* databaseController{nullptr};

    NavigationController* navigationController{nullptr};

    Game* newGame{nullptr};

    Game* selectedGame{nullptr};

    GameSearch* gameSearch{nullptr};

    TCPClient* tcpClient{nullptr};

    TCPClientsList* tcpClientsList{nullptr};

    Settings* settings{nullptr};


    QList<TCPClientCommand*> gameViewContextTCPClientCommands{};

    QList<Command*> gameViewContextCommands{};

    QList<Command*> addQuestionPanelContextCommands{};

    QList<Command*> settingsViewContextCommands{};
};

CommandController::CommandController(QObject *parent, TCPController* tcpController, IDatabaseController* databaseController, NavigationController* navigationController , Game* newGame, Game *selectedGame, GameSearch* gameSearch, TCPClient* tcpClient, TCPClientsList* tcpClientsList, Settings* settings)
    : QObject(parent)
{
    implementation.reset(new Implementation(this, tcpController,databaseController, navigationController ,newGame,selectedGame ,gameSearch, tcpClient, tcpClientsList, settings));
}

CommandController::~CommandController(){}

QQmlListProperty<Command> CommandController::ui_addQuestionPanelContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->addQuestionPanelContextCommands);
}



QQmlListProperty<Command> CommandController::ui_gameViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->gameViewContextCommands);
}

QQmlListProperty<Command> CommandController::ui_settingsViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->settingsViewContextCommands);
}

QQmlListProperty<TCPClientCommand> CommandController::ui_gameViewContextTCPClientCommands()
{
    return QQmlListProperty<TCPClientCommand>(this, implementation->gameViewContextTCPClientCommands);
}


void CommandController::onCreateGameSaveExecuted()
{
    qDebug() << "You executed the Save command!";

    implementation->databaseController->createRow(implementation->newGame->key(), implementation->newGame->num(), implementation->newGame->toJson());

//    implementation->gameSearch->searchText()->setValue("*");
//    implementation->gameSearch->searchText()->setValue(implementation->newGame->id());

//    implementation->gameSearch->search();
    implementation->newGame->clear();

    implementation->gameSearch->searchAll();

//    implementation->navigationController->goFindGameView();

    qDebug() << "New client saved.";
}

void CommandController::onSaveSettingsExecuted()
{
    qDebug() << "You executed the Save Settings command!";
//    qDebug() << implementation->settings->quantity->value();
    qDebug() << implementation->settings->quantity->value();
    qDebug() << QString::number(implementation->settings->askQuestions->value());
    implementation->databaseController->createRow(implementation->settings->key(), "1", implementation->settings->toJson());
}

void CommandController::onEditGameSaveExecuteed()
{
    qDebug () << "SAVE EXECUTED";

//    implementation->databaseController->updateRow(implementation->newGame->key(), implementation->newGame->num(),implementation->newGame->toJson());

    implementation->databaseController->updateRow(implementation->selectedGame->key(), implementation->selectedGame->num(), implementation->selectedGame->toJson());

    implementation->gameSearch->searchAll();

    qDebug() << "Game updated.";

}

void CommandController::onTCPClientExecuted()
{
    qDebug() << "You executed TCP client click!!!";
}


void CommandController::setSelectedGame(Game *game)
{
    implementation->selectedGame = game;
    qDebug() << "Selected Game: " << game->text->value();
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

//void CommandController::onFindGameSearchExecuted()
//{
//    qDebug() << "You executed the Search command";

//    implementation->gameSearch->search();
//}

//void CommandController::onEditGameSaveExecuted()
//{
//    qDebug() << "You executed Save command";

//    implementation->databaseController->updateRow(implementation->selectedGame->key(), implementation->selectedGame->id(), implementation->selectedGame->toJson());

//    qDebug() << "Udated game saved";
//}

//void CommandController::onEditGameDeleteExecuted()
//{
//    qDebug() << "You executed the Delete command!";

//    implementation->databaseController->deleteRow(implementation->selectedGame->key(), implementation->selectedGame->id());
//    implementation->selectedGame = nullptr;

//    qDebug() << "Game Deleted";

//    implementation->gameSearch->search();
//    implementation->navigationController->goDashboardView();
//}

//QQmlListProperty<Command> CommandController::ui_findGameViewContextCommands()
//{
//    return QQmlListProperty<Command>(this, implementation->findGameViewContextCommands);
//}

//QQmlListProperty<Command> CommandController::ui_editGameViewContextCommands()
//{
//    return QQmlListProperty<Command>(this, implementation->editGameViewContextCommands);
//}

}
}

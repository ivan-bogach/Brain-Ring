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
        , settings(_settings)
        , newGame(_newGame)
        , selectedGame(_selectedGame)
        , gameSearch(_gameSearch)
        , tcpClient(_tcpClient)
        , tcpClientsList(_tcpClientsList)
    {
//AddQuestionPanel
        Command* createGameSaveCommand =  new Command(commandController, QChar( 0xf0c7 ), "Сохранить");
        QObject::connect(createGameSaveCommand, &Command::executed, commandController, &CommandController::onCreateGameSaveExecuted);
        addQuestionPanelContextCommands.append(createGameSaveCommand);

//SettingsView
        Command* startSettingsCommand = new Command(commandController, "", "");
        QObject::connect(startSettingsCommand, &Command::executed, commandController, &CommandController::onStartSettingsView);
        settingsViewContextCommands.append(startSettingsCommand);

        Command* saveSettings = new Command(commandController, QChar( 0xf0c7 ), "Сохранить");
        QObject::connect(saveSettings, &Command::executed, commandController, &CommandController::onSaveSettingsExecuted);
        settingsViewContextCommands.append(saveSettings);

//GameView
        Command* startServerCommand = new Command(commandController, QChar(0xf0c7), "Старт");
        QObject::connect(startServerCommand, &Command::executed, commandController, &CommandController::onStartServerExecuted);
        gameViewContextCommands.append(startServerCommand);

        Command* stopServerCommand = new Command(commandController, QChar(0xf0c7), "Старт");
        QObject::connect(stopServerCommand, &Command::executed, commandController, &CommandController::onStopServerExecuted);
        gameViewContextCommands.append(stopServerCommand);
    }

    CommandController* commandController{nullptr};

    TCPController* tcpController{nullptr};

    IDatabaseController* databaseController{nullptr};

    NavigationController* navigationController{nullptr};

    Settings* settings{nullptr};

    Game* newGame{nullptr};

    Game* selectedGame{nullptr};

    GameSearch* gameSearch{nullptr};

    TCPClient* tcpClient{nullptr};

    TCPClientsList* tcpClientsList{nullptr};



//    QList<TCPClientCommand*> gameViewContextTCPClientCommands{};

    QList<Command*> gameViewContextCommands{};

    QList<Command*> addQuestionPanelContextCommands{};

    QList<Command*> settingsViewContextCommands{};
};

CommandController::CommandController(QObject *parent, TCPController* tcpController, IDatabaseController* databaseController, NavigationController* navigationController , Game* newGame, Game *selectedGame, GameSearch* gameSearch, TCPClient* tcpClient, TCPClientsList* tcpClientsList, Settings* settings)
    : QObject(parent)
{
//    qDebug() << "Command Controller Initialized";
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

void CommandController::onCreateGameSaveExecuted()
{
//    qDebug() << "You executed the Save command!";

    implementation->databaseController->createRow(implementation->newGame->key(), implementation->newGame->number()->value(), implementation->newGame->toJson());

    implementation->newGame->clear();

    implementation->gameSearch->searchAll();

//    qDebug() << "New client saved.";
}

void CommandController::onStartSettingsView()
{
     QJsonObject jsonObject = implementation->databaseController->readRow("settings", "1");
     implementation->settings->askQuestions()->setValue(jsonObject.value("ask").toInt());
     implementation->settings->quantity()->setValue(jsonObject.value("quantity").toInt());
//     qDebug() << "Command controller: Settings view started!";
}

void CommandController::onSaveSettingsExecuted()
{
    qDebug() << "You executed the Save Settings command!";
    implementation->databaseController->createRow(implementation->settings->key(), "1", implementation->settings->toJson());
    implementation->navigationController->goDashboardView();
}

void CommandController::onEditGameSaveExecuteed()
{
//    qDebug () << "SAVE EXECUTED";

    implementation->databaseController->updateRow(implementation->selectedGame->key(), implementation->selectedGame->number()->value(), implementation->selectedGame->toJson());

    implementation->gameSearch->searchAll();

//    qDebug() << "Game updated.";

}


void CommandController::setSelectedGame(Game *game)
{
    implementation->selectedGame = game;
//    qDebug() << "Selected Game: " << game->text->value();
}


void CommandController::onStartServerExecuted()
{
//    qDebug() << "Command controller: You executed the Start command!";
    implementation->tcpController->startServer();

    QJsonObject jsonObject = implementation->databaseController->readRow("settings", "1");
    implementation->settings->askQuestions()->setValue(jsonObject.value("ask").toInt());
    implementation->settings->quantity()->setValue(jsonObject.value("quantity").toInt());

//    qDebug() << "Command controller: server started with quantity" << QString::number(implementation->settings->quantity()->value());
}


void CommandController::onStopServerExecuted()
{
    qDebug() << "Command controller: You executed the STOP command!";
    implementation->tcpController->stopServer();
    qDebug() << "Command controller: server stoped!";
}

}
}

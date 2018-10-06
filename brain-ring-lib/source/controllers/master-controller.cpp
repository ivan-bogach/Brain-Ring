#include "master-controller.h"

using namespace br::models;

namespace br {
namespace controllers {

class MasterController::Implementation
{
public:
	explicit Implementation(MasterController* _masterController)
        : masterController(_masterController)
    {
        databaseController = new DatabaseController(masterController);
        navigationController = new NavigationController(masterController);
        tcpController = new TCPController(masterController);
        newGame = new Game(masterController);
        selectedGame = new Game(masterController);
        gameSearch = new GameSearch(masterController, databaseController);
        tcpClient = new TCPClient(masterController);
        tcpClientList = new TCPClientsList(masterController, tcpController);
        commandController = new CommandController(masterController, tcpController, databaseController, navigationController, newGame, selectedGame, gameSearch);
    }

    MasterController* masterController{nullptr};
    CommandController* commandController{nullptr};
    DatabaseController* databaseController{nullptr};
    NavigationController* navigationController{nullptr};
    TCPController* tcpController{nullptr};
    Game* newGame{nullptr};
    Game* selectedGame{nullptr};
    GameSearch* gameSearch{nullptr};
    TCPClient* tcpClient{nullptr};
    TCPClientsList* tcpClientList{nullptr};

    QString welcomeMessage = "This is MasterController to MJBHjk  qaslkfjklasd";
};

MasterController::MasterController(QObject *parent) : QObject(parent)
{
    implementation.reset(new Implementation(this));
}

MasterController::~MasterController(){}

CommandController* MasterController::commandController()
{
    return implementation->commandController;
}

DatabaseController* MasterController::databaseController()
{
    return implementation->databaseController;
}

NavigationController* MasterController::navigationController()
{
    return implementation->navigationController;
}

TCPController* MasterController::tcpController()
{
    return implementation->tcpController;
}


const QString& MasterController::welcomeMessage() const
{
    return implementation->welcomeMessage;
}

Game* MasterController::newGame()
{
    return implementation->newGame;
}

Game* MasterController::selectedGame()
{
    return implementation->selectedGame;
}

GameSearch* MasterController::gameSearch()
{
    return implementation->gameSearch;
}

TCPClient* MasterController::tcpClient()
{
    return implementation->tcpClient;
}

TCPClientsList* MasterController::tcpClientList()
{
    return implementation->tcpClientList;
}

//void MasterController::selectGame(Game *game)
//{
//    implementation->navigationController->goEditGameView(game);
//}

}}


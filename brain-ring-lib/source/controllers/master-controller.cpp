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
        gameSearch = new GameSearch(masterController, databaseController);
        commandController = new CommandController(masterController, tcpController, databaseController, navigationController, newGame, gameSearch);
    }

    MasterController* masterController{nullptr};
    CommandController* commandController{nullptr};
    DatabaseController* databaseController{nullptr};
    NavigationController* navigationController{nullptr};
    TCPController* tcpController{nullptr};
    Game* newGame{nullptr};
    GameSearch* gameSearch{nullptr};
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

GameSearch* MasterController::gameSearch()
{
    return implementation->gameSearch;
}

void MasterController::selectGame(Game *game)
{
    implementation->navigationController->goEditGameView(game);
}

}}


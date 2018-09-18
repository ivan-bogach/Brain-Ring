#include "master-controller.h"

using namespace br::models;

namespace br {
namespace controllers {

class MasterController::Implementation
{
public:
    Implementation(MasterController* _masterController)
        : masterController(_masterController)
    {
        commandController = new CommandController(masterController);
        databaseController = new DatabaseController(masterController);
        newGame = new Game(masterController);
        navigationController = new NavigationController(masterController);
    }

    MasterController* masterController{nullptr};
    CommandController* commandController{nullptr};
    DatabaseController* databaseController{nullptr};
    NavigationController* navigationController{nullptr};
    Game* newGame{nullptr};
    QString welcomeMessage = "This is MasterController to MJBHjk  qaslkfjklasd";
};

MasterController::MasterController(QObject *parent) : QObject(parent)
{
    implementation.reset(new Implementation(this));
}

MasterController::~MasterController(){}

NavigationController* MasterController::navigationController()
{
    return implementation->navigationController;
}

CommandController* MasterController::commandController()
{
    return implementation->commandController;
}

const QString& MasterController::welcomeMessage() const
{
    return implementation->welcomeMessage;
}

Game* MasterController::newGame()
{
    return implementation->newGame;
}

}}


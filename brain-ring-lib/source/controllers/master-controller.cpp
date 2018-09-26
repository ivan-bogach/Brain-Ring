#include "master-controller.h"

using namespace br::models;

namespace br {
namespace controllers {

class MasterController::Implementation
{
public:
    explicit Implementation(MasterController* _masterController)
        :masterController(_masterController)
    {
        navigationController = new NavigationController(masterController);
        commandController = new Commandcontroller(masterController);
        newGame = new Game(masterController);
    }

    MasterController* masterController{nullptr};
    Commandcontroller* commandController{nullptr};
    NavigationController* navigationController{nullptr};
    Game* newGame{nullptr};
    QString welcomeMessage = "Welcome message";
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

Commandcontroller* MasterController::commandController()
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

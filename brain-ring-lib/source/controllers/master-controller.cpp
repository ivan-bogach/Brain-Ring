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
        databaseController = new DatabaseController(masterController);
        navigationController = new NavigationController(masterController);
        newGame = new Game(masterController);
        commandController = new Commandcontroller(masterController, databaseController, navigationController, newGame);
    }

    MasterController* masterController{nullptr};
    Commandcontroller* commandController{nullptr};
    DatabaseController* databaseController{nullptr};
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

DatabaseController* MasterController::databaseController()
{
    return implementation->databaseController;
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

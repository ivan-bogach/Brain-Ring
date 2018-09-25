#include "master-controller.h"

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
    }

    MasterController* masterController{nullptr};
    Commandcontroller* commandController{nullptr};
    NavigationController* navigationController{nullptr};
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

}}

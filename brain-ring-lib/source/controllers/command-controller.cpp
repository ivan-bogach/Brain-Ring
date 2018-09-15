#include "command-controller.h"

#include <QList>
#include <QDebug>

using namespace br::framework;

namespace br {
namespace controllers {

class CommandController::Implementation
{
public:
    Implementation(CommandController* _commandController)
        : commandController(_commandController)
    {
        Command* createGameSaveCommand =  new Command(commandController, QChar( 0xf0c7 ), "Сохранить");

// connect	the	 executed() signal of the command to the onCreateGmaeSaveExecuted() slot of the CommandController
        QObject::connect(createGameSaveCommand, &Command::executed, commandController, &CommandController::onCreateGameSaveExecuted);
        createGameViewContextCommands.append(createGameSaveCommand);
    }

    CommandController* commandController{nullptr};
    QList<Command*> createGameViewContextCommands{};
};

CommandController::CommandController(QObject *parent) : QObject(parent)
{
    implementation.reset(new Implementation(this));
}

CommandController::~CommandController(){}

QQmlListProperty<Command> CommandController::ui_createGameViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->createGameViewContextCommands);
}

void CommandController::onCreateGameSaveExecuted()
{
    qDebug() << "Save"
;}

}
}

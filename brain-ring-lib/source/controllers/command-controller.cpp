#include "command-controller.h"

#include <QList>
#include <QDebug>

using namespace br::framework;

namespace br {
namespace controllers {

class Commandcontroller::Implementation
{
public:
    Implementation(Commandcontroller* _commandController)
        : commandcontroller(_commandController)
    {
        Command* createGameSaveCommand = new Command(commandcontroller, QChar( 0xf0c7 ), "Сохранить");
        QObject::connect(createGameSaveCommand, &Command::executed, commandcontroller, &Commandcontroller::onCreateGameSaveExecuted);
        createGameViewContextCommands.append(createGameSaveCommand);
    }

    Commandcontroller* commandcontroller{nullptr};
    QList<Command*> createGameViewContextCommands{};
};

Commandcontroller::Commandcontroller(QObject *parent) : QObject(parent)
{
    implementation.reset(new Implementation(this));
}

Commandcontroller::~Commandcontroller() {}

QQmlListProperty<Command> Commandcontroller::ui_createGameViewContextCommands()
{
    return QQmlListProperty<Command>(this, implementation->createGameViewContextCommands);
}

void Commandcontroller::onCreateGameSaveExecuted()
{
    qDebug() << "SAVE EXECUTED";
}

}
}

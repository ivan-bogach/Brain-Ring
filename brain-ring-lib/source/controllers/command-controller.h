#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <QtQml/QQmlListProperty>


#include <brain-ring-lib_global.h>
#include <framework/command.h>
#include <controllers/i-database-controller.h>
#include <models/game.h>

namespace br {
namespace controllers {

class BRAINRINGLIBSHARED_EXPORT CommandController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<br::framework::Command> ui_createGameViewContextCommands READ ui_createGameViewContextCommands CONSTANT)


public:
    explicit CommandController(QObject* _parent = nullptr, IDatabaseController* databaseController = nullptr, models::Game* newGame= nullptr);
    ~CommandController();

//QQmlListProperty enables QML to interact with a list of custom objects
    QQmlListProperty<framework::Command> ui_createGameViewContextCommands();

signals:

public slots:
    void onCreateGameSaveExecuted();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}


#endif // COMMANDCONTROLLER_H

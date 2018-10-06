#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include <brain-ring-lib_global.h>
#include <framework/command.h>
#include <framework/tcpclientcommand.h>
#include <controllers/i-database-controller.h>
#include <controllers/navigation-controller.h>
#include <controllers/tcp-controller.h>
#include <models/game.h>
#include <models/gamesearch.h>
#include <models/tcpclient.h>
#include <models/tcpclientslist.h>

namespace br {
namespace controllers {

class BRAINRINGLIBSHARED_EXPORT CommandController : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(QQmlListProperty<br::framework::Command> ui_createGameViewContextCommands READ ui_createGameViewContextCommands CONSTANT)
//    Q_PROPERTY(QQmlListProperty<br::framework::Command> ui_findGameViewContextCommands READ ui_findGameViewContextCommands CONSTANT)
//    Q_PROPERTY(QQmlListProperty <br::framework::Command> ui_editGameViewContextCommands READ ui_editGameViewContextCommands CONSTANT)

    Q_PROPERTY(QQmlListProperty <br::framework::Command> ui_gameViewContextCommands READ ui_gameViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty <br::framework::TCPClientCommand> ui_gameViewContextTCPClientCommands READ ui_gameViewContextTCPClientCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<br::framework::Command> ui_addQuestionPanelContextCommands READ ui_addQuestionPanelContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<br::framework::Command> ui_editQuestionListContextCommands READ ui_editQuestionListContextCommands CONSTANT)

public:
    explicit CommandController(QObject* _parent = nullptr,
                               TCPController* tcpController = nullptr,
                               IDatabaseController* databaseController = nullptr,
                               NavigationController* navigationController = nullptr,
                               models::Game* newGame= nullptr,
                               models::Game* selectedGame = nullptr,
                               models::GameSearch* gameSearch = nullptr,
                               models::TCPClient* tcpClient = nullptr,
                               models::TCPClientsList* tcpClientsList = nullptr
                               );
    ~CommandController();

    QQmlListProperty<framework::Command> ui_gameViewContextCommands();
    QQmlListProperty<framework::Command> ui_addQuestionPanelContextCommands();
    QQmlListProperty<framework::Command> ui_editQuestionListContextCommands();
    QQmlListProperty<framework::TCPClientCommand> ui_gameViewContextTCPClientCommands();



//    QQmlListProperty<framework::Command> ui_createGameViewContextCommands();
//    QQmlListProperty enables QML to interact with a list of custom objects
//    QQmlListProperty<framework::Command> ui_findGameViewContextCommands();
//    QQmlListProperty<framework::Command> ui_editGameViewContextCommands();

signals:

public slots:
    void setSelectedGame(br::models::Game* game);

    void onCreateGameSaveExecuted();
//    void onFindGameSearchExecuted();
//    void onEditGameSaveExecuted();
//    void onEditGameDeleteExecuted();
    void onEditGameSaveExecuteed();

    void onStartServerExecuted();
    void onStopServerExecuted();

    void onTCPClientExecuted();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}


#endif // COMMANDCONTROLLER_H

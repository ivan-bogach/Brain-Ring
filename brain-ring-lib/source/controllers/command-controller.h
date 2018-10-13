#ifndef COMMANDCONTROLLER_H
#define COMMANDCONTROLLER_H

#include <QObject>
#include <QtQml/QQmlListProperty>
#include <QString>

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
#include <models/settings.h>
#include <gameplay/player.h>

namespace br {
namespace controllers {

class BRAINRINGLIBSHARED_EXPORT CommandController : public QObject
{
    Q_OBJECT
//    Q_PROPERTY(QQmlListProperty <br::framework::TCPClientCommand> ui_gameViewContextTCPClientCommands READ ui_gameViewContextTCPClientCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty <br::framework::Command> ui_gameViewContextCommands READ ui_gameViewContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<br::framework::Command> ui_addQuestionPanelContextCommands READ ui_addQuestionPanelContextCommands CONSTANT)
    Q_PROPERTY(QQmlListProperty<br::framework::Command> ui_settingsViewContextCommands READ ui_settingsViewContextCommands CONSTANT)
//    Q_PROPERTY(type name READ name WRITE setName NOTIFY nameChanged)

public:
    explicit CommandController(QObject* _parent = nullptr,
                               IDatabaseController* databaseController = nullptr,
                               gameplay::Player* newPlayer = nullptr,
                               TCPController* tcpController = nullptr,
                               NavigationController* navigationController = nullptr,
                               models::Game* newGame= nullptr,
                               models::Game* selectedGame = nullptr,
                               models::GameSearch* gameSearch = nullptr,
                               models::TCPClient* tcpClient = nullptr,
                               models::TCPClientsList* tcpClientsList = nullptr,
                               models::Settings* settings = nullptr
                               );
    ~CommandController();

    QQmlListProperty<framework::Command> ui_gameViewContextCommands();
    QQmlListProperty<framework::Command> ui_addQuestionPanelContextCommands();
    QQmlListProperty<framework::Command> ui_settingsViewContextCommands();
//    QQmlListProperty<framework::TCPClientCommand> ui_gameViewContextTCPClientCommands();

signals:

public slots:
    void setSelectedGame(br::models::Game* game);
    void onCreateGameSaveExecuted();
    void onEditGameSaveExecuteed();
    void onStartServerExecuted();
    void onStopServerExecuted();
//    void onTCPClientExecuted();
    void onSaveSettingsExecuted();
    void onStartSettingsView();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}


#endif // COMMANDCONTROLLER_H

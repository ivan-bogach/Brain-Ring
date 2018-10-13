#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include <brain-ring-lib_global.h>
#include <controllers/command-controller.h>
#include <controllers/database-controller.h>
#include <controllers/navigation-controller.h>
#include <controllers/tcp-controller.h>
#include <models/game.h>
#include <models/gamesearch.h>
#include <models/tcpclient.h>
#include <models/tcpclientslist.h>
#include <models/settings.h>
#include <gameplay/player.h>
#include <gameplay/gameplay.h>


namespace br {
namespace controllers {

//to use this class outside of this project (in the UI project), BRAINRINGLIBSHARED_EXPORT macro
class BRAINRINGLIBSHARED_EXPORT MasterController : public QObject
{
//inherit from QObject requires Q_OBJECT macro and an overloaded constructor that takes a QObject parent.
    Q_OBJECT

//CommandCoordinator 	properties:
// creating	a new	property of the	QString	type to be able to ACCESS this member FROM QML
// refer to the property	as ui_welcomeMessage and get (or set) the	value in the MEMBER welcomeMessage
    Q_PROPERTY(QString ui_welcomeMessage READ welcomeMessage CONSTANT)

//br::controllers:: because UI QML is not executing within the scope of br namespace
    Q_PROPERTY(br::controllers::NavigationController* ui_navigationController READ navigationController CONSTANT)
    Q_PROPERTY( br::controllers::DatabaseController* ui_databaseController READ databaseController CONSTANT )
    Q_PROPERTY(br::controllers::TCPController* ui_tcpController READ tcpController CONSTANT)
    Q_PROPERTY(br::controllers::CommandController* ui_commandController READ commandController CONSTANT)
    Q_PROPERTY(br::models::Game* ui_newGame READ newGame CONSTANT)
    Q_PROPERTY(br::models::Game* ui_selectedGame READ selectedGame CONSTANT)
    Q_PROPERTY(br::models::GameSearch* ui_gameSearch READ gameSearch CONSTANT)
    Q_PROPERTY(br::models::TCPClient* ui_tcpClient READ tcpClient CONSTANT)
    Q_PROPERTY(br::models::TCPClientsList* ui_tcpClientList READ tcpClientList CONSTANT)
    Q_PROPERTY(br::models::Settings* ui_settings READ settings CONSTANT)
    Q_PROPERTY(br::gameplay::Player* ui_player READ player CONSTANT)
    Q_PROPERTY(br::gameplay::GamePlay* ui_gamePlay READ gamePlay CONSTANT)

public:
    explicit MasterController(QObject* parent = nullptr);
    ~MasterController();

//Accessor methods:
    CommandController* commandController();

    DatabaseController* databaseController();

    gameplay::Player* player();

    TCPController* tcpController();

    NavigationController* navigationController();

    models::Game* newGame();

    models::Game* selectedGame();

    models::GameSearch* gameSearch();

    models::TCPClient* tcpClient();

    models::TCPClientsList* tcpClientList();

    models::Settings* settings();

    gameplay::GamePlay* gamePlay();

    const QString& welcomeMessage() const;

signals:

public slots:
//    void selectGame(br::models::Game* game);

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}

#endif // MASTERCONTROLLER_H

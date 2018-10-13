#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QObject>

#include <QScopedPointer>
#include <QtQml/QQmlListProperty>

#include "brain-ring-lib_global.h"
#include <controllers/tcp-controller.h>
#include <controllers/i-database-controller.h>
#include <data/entity.h>
#include <data/stringdecorator.h>
#include <data/intdecorator.h>
#include <models/settings.h>
#include <gameplay/player.h>

namespace br {
namespace gameplay {

class BRAINRINGLIBSHARED_EXPORT GamePlay : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(br::data::IntDecorator* ui_isQuestion READ isQuestion CONSTANT)
    Q_PROPERTY(br::data::IntDecorator* ui_numberPlayersInSettings READ numberPlayersInSettings CONSTANT)

    Q_PROPERTY(bool ui_isAllClientsConnected READ isAllClientsConnected NOTIFY allClientsConnected)
    Q_PROPERTY(QQmlListProperty<br::gameplay::Player> ui_players READ ui_players NOTIFY playersChanged)

public:
    explicit GamePlay(QObject* parent = nullptr, models::Settings* settings = nullptr, controllers::TCPController* tcpController = nullptr, controllers::IDatabaseController* databaseController = nullptr);
    ~GamePlay();

//    void clear();
    void searchAll();
//    void addPlayer();

    bool isAllClientsConnected();
    data::IntDecorator* isQuestion();
    data::IntDecorator* numberPlayersInSettings();
    int numberConnectedPlayers();
    QQmlListProperty<Player> ui_players();



signals:
    void playersChanged();
    void allClientsConnected();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

};


}
}


#endif // GAMEPLAY_H

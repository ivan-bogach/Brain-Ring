#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QObject>
#include <QScopedPointer>
#include <QtQml/QQmlListProperty>
#include <QJsonObject>
#include <QJsonValue>

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
    Q_PROPERTY(QQmlListProperty<br::gameplay::Player> ui_players READ ui_players NOTIFY playersListChanged)
    Q_PROPERTY(bool ui_isAllPlayersConnected READ isAllPlayersConnected NOTIFY playersListChanged)
//    Q_PROPERTY(bool ui_isRaundStarted READ isRaundStarted NOTIFY raundStarted)

public:
    explicit GamePlay(QObject* parent = nullptr, models::Settings* settings = nullptr, controllers::TCPController* tcpController = nullptr, controllers::IDatabaseController* databaseController = nullptr);
    ~GamePlay();

    void scan();
    void getMessageFromTCP(const QByteArray &);
    void clear();

    QQmlListProperty<Player> ui_players();
    bool isAllPlayersConnected();
//    bool isRaundStarted();

signals:
    void playersListChanged();
//    void raundStarted();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

};


}
}


#endif // GAMEPLAY_H

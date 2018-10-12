#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <QObject>

#include "brain-ring-lib_global.h"
#include <controllers/tcp-controller.h>
#include <data/entity.h>
#include <data/stringdecorator.h>
#include <data/intdecorator.h>
#include <models/settings.h>

namespace br {
namespace gameplay {

class BRAINRINGLIBSHARED_EXPORT GamePlay : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(bool* ui_isAllClientsConnected READ isAllClientsConnected CONSTANT)
    Q_PROPERTY(br::data::IntDecorator* ui_isQuestion READ isQuestion CONSTANT)
    Q_PROPERTY(br::data::IntDecorator* ui_numberPlayersInSettings READ numberPlayersInSettings CONSTANT)
    Q_PROPERTY(int ui_numberConnectedPlayers READ numberConnectedPlayers CONSTANT)

public:
    explicit GamePlay(QObject* parent = nullptr, models::Settings* settings = nullptr, controllers::TCPController* tcpController = nullptr);
    ~GamePlay();

    void clear();

    bool isAllClientsConnected();
    data::IntDecorator* isQuestion();
    data::IntDecorator* numberPlayersInSettings();
    int numberConnectedPlayers();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

};


}
}


#endif // GAMEPLAY_H

#include "gameplay.h"

using namespace br::models;
using namespace br::data;
using namespace br::controllers;

namespace br {
namespace gameplay {

class GamePlay::Implementation
{
public:
    Implementation(GamePlay* _gamePlay, Settings* _settings, TCPController* _tcpController)
        : gamePlay(_gamePlay)
        , settings(_settings)
        , tcpController(_tcpController)
    {}
    GamePlay gamePlay{nullptr};
    Settings settings{nullptr};
    TCPController* tcpController{nullptr};

    bool isAllClientsConnected{nullptr};
    IntDecorator* isQuestion{nullptr};
    IntDecorator* numberPlayersInSettings{nullptr};
    int numberConnectedPlayers;
};

GamePlay::GamePlay(QObject* parent, Settings* settings, controllers::TCPController *tcpController)
    : Entity(parent, "gamePlay")
{
    implementation.reset(new Implementation(this, settings, tcpController));

    implementation->isAllClientsConnected = false;
    implementation->isQuestion = implementation->settings.askQuestions();
    implementation->numberPlayersInSettings = implementation->settings.quantity();
}

GamePlay::~GamePlay(){}

bool GamePlay::isAllClientsConnected()
{
    implementation->numberConnectedPlayers = implementation->tcpController->SClients().size();
    return (implementation->numberPlayersInSettings->value() - implementation->numberConnectedPlayers == 0);
}

IntDecorator* GamePlay::isQuestion()
{
    return implementation->isQuestion;
}

IntDecorator* GamePlay::numberPlayersInSettings()
{
    return implementation->numberPlayersInSettings;
}

}
}

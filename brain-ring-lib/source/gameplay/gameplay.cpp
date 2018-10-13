#include "gameplay.h"

using namespace br::models;
using namespace br::data;
using namespace br::controllers;

namespace br {
namespace gameplay {

class GamePlay::Implementation
{
public:
    Implementation(GamePlay* _gamePlay, Settings* _settings, TCPController* _tcpController, IDatabaseController* _databaseControler)
        : gamePlay(_gamePlay)
        , settings(_settings)
        , tcpController(_tcpController)
        , databaseControler(_databaseControler)
    {}
    GamePlay gamePlay{nullptr};
    Settings settings{nullptr};
    TCPController* tcpController{nullptr};
    IDatabaseController* databaseControler{nullptr};

    bool isAllClientsConnected{nullptr};
    IntDecorator* isQuestion{nullptr};
    IntDecorator* numberPlayersInSettings{nullptr};
    int numberConnectedPlayers;

    EntityCollection<Player>* playersList{nullptr};
};

GamePlay::GamePlay(QObject* parent, Settings* settings, TCPController* tcpController, IDatabaseController* databaseController)
    : Entity(parent, "gamePlay")
{
    implementation.reset(new Implementation(this, settings, tcpController, databaseController));
    implementation->playersList = static_cast<EntityCollection<Player>*>(addChildCollection(new EntityCollection<Player>(this, "playersList")));

    implementation->isAllClientsConnected = false;
    implementation->isQuestion = implementation->settings.askQuestions();
    implementation->numberPlayersInSettings = implementation->settings.quantity();

    connect(implementation->playersList, &EntityCollection<Player>::collectionChanged, this, &GamePlay::playersChanged);
    connect(implementation->tcpController, &TCPController::tcpClientArrived, this, &GamePlay::searchAll);
}

GamePlay::~GamePlay(){}

QQmlListProperty<Player> GamePlay::ui_players()
{
    return QQmlListProperty<Player>(this, implementation->playersList->derivedEntities());
}

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

void GamePlay::searchAll()
{
    auto resultsArray = implementation->databaseControler->findAll("players");
    implementation->playersList->update(resultsArray);
}

//void GamePlay::addPlayer()
//{
//    implementation->databaseControler->
//}

}
}

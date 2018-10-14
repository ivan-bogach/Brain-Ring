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
    GamePlay* gamePlay{nullptr};
    Settings* settings{nullptr};
    TCPController* tcpController{nullptr};
    IDatabaseController* databaseControler{nullptr};

    EntityCollection<Player>* playersList{nullptr};

    QMap <QString, int> gamePoints;
};

GamePlay::GamePlay(QObject* parent, Settings* settings, TCPController* tcpController, IDatabaseController* databaseController)
    : Entity(parent, "gamePlay")
{

    implementation.reset(new Implementation(this, settings, tcpController, databaseController));

    implementation->playersList = static_cast<EntityCollection<Player>*>(addChildCollection(new EntityCollection<Player>(this, "player")));

    connect(implementation->playersList, &EntityCollection<Player>::collectionChanged, this, &GamePlay::playersListChanged);

    connect(implementation->tcpController, &TCPController::tcpClientArrived, this, &GamePlay::scan);

    int numberPlayersFromSettings = implementation->settings->quantity()->value();

    QJsonArray resultsArray;
    QJsonObject jsonObject;

    for (int i =1; i <= numberPlayersFromSettings; ++i)
    {
        jsonObject.insert("number", QString::number(i));
        jsonObject.insert("isConnected", "");
        jsonObject.insert("points", "0");

       resultsArray.append(QJsonValue(jsonObject));
    }
    implementation->playersList->update(resultsArray);
}

GamePlay::~GamePlay(){}

QQmlListProperty<Player> GamePlay::ui_players()
{
    qDebug() << "GamePlay::ui_players done! With: " << implementation->playersList->derivedEntities().size();
    return QQmlListProperty<Player>(this, implementation->playersList->derivedEntities());
}

void GamePlay::scan()
{
    //get number of players from settings and initialize Qmap with size equal number and filled falses
        int numberPlayersFromSettings = implementation->settings->quantity()->value();

        QMap<QString, bool> jsonMap;
        for(int i = 1; i <= numberPlayersFromSettings; ++i)
        {
            jsonMap[QString::number(i)] = false;
        }


    //for updating EntityCollection create QJsonArray and QJsonObject for fill QJsonArray
        QJsonArray returnArray;
        QJsonObject jsonObject;

    //get from tcpcontroller connected clients and for each ip insert "ip" in JsonObject
        QMapIterator<int, QTcpSocket *> i(implementation->tcpController->SClients());
        while (i.hasNext())
        {
    //insert last number of client`s ip in jsonObject
            i.next();
            QString entireIp = i.value()->peerAddress().toString();
            int sizeIP =entireIp.size();
            QString ip = QString(entireIp[sizeIP - 1]);
            jsonObject.insert("number", ip);
    //insert true for connected ip in jsonMap
            jsonMap[ip] = true;

        }

        QMap<QString, bool>::iterator it = jsonMap.begin();
        for(; it != jsonMap.end(); ++it)
        {
            if(it.value() == false)
            {
                jsonObject.insert("number", it.key());
                jsonObject.insert("isConnected", "");
                jsonObject.insert("points", "0");
            }
            else if(it.value() == true)
            {
                jsonObject.insert("number", it.key());
                jsonObject.insert("isConnected", "true");
                jsonObject.insert("points", implementation->gamePoints[it.key()]);
            }
            returnArray.append(QJsonValue(jsonObject));
        }
        implementation->playersList->update(returnArray);
        qDebug() << "GamePlay::scan done!";
}

}
}

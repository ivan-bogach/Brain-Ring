#include "gameplay.h"

using namespace br::models;
using namespace br::data;
using namespace br::controllers;

namespace br {
namespace gameplay {

class GamePlay::Implementation
{
public:
    Implementation(GamePlay* _gamePlay, Settings* _settings, TCPController* _tcpController, IDatabaseController* _databaseControler, NavigationController* _navigationController, Game* _game)
        : gamePlay(_gamePlay)
        , settings(_settings)
        , tcpController(_tcpController)
        , databaseControler(_databaseControler)
        , navigationController(_navigationController)
        , game(_game)
    {}
    GamePlay* gamePlay{nullptr};
    Settings* settings{nullptr};
    TCPController* tcpController{nullptr};
    IDatabaseController* databaseControler{nullptr};
    NavigationController* navigationController{nullptr};
    Game* game{nullptr};

//    bool isRaundStarted;

    EntityCollection<Player>* playersList{nullptr};

    bool allPlayerConnected;
    bool gameStarted;
    bool isFirstQuestion;
    bool waitAnswer;
    bool nextQuestion;
    bool aDisabled;
    bool inEmtyQuestionList;


    QMap <QString, int> gamePoints;
    QMap <QString, int> gameAttempts;

    StringDecorator* playerNumber{nullptr};

     data::EntityCollection<Game>* questions{nullptr};
};

GamePlay::GamePlay(QObject* parent, Settings* settings, TCPController* tcpController, IDatabaseController* databaseController, NavigationController* navigationController, Game* game)
    : Entity(parent, "gamePlay")
{

    implementation.reset(new Implementation(this, settings, tcpController, databaseController, navigationController, game));

    implementation->playersList = static_cast<EntityCollection<Player>*>(addChildCollection(new EntityCollection<Player>(this, "player")));

    implementation->playerNumber = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "number", "Номер")));

    implementation->questions = static_cast<EntityCollection<Game>*>(addChildCollection(new EntityCollection<Game>(this, "questions")));

    implementation->allPlayerConnected = false;

    implementation->gameStarted = false;

    implementation->waitAnswer = false;

    implementation->isFirstQuestion = true;

    implementation->nextQuestion =  true;

//"a"="n" from tcp rc
    implementation->aDisabled = false;

    implementation->inEmtyQuestionList = false;


    connect(implementation->playersList, &EntityCollection<Player>::collectionChanged, this, &GamePlay::playersListChanged);

    connect(implementation->tcpController, &TCPController::tcpClientArrived, this, &GamePlay::scan);

    connect(implementation->databaseControler, &IDatabaseController::databaseChanged, this, &GamePlay::scan);

    connect(implementation->tcpController, &TCPController::messageArrived, this, &GamePlay::getMessageFromTCP);

    QJsonArray resultsArray;
    QJsonObject jsonObject;


    int numberPlayersFromSettings = implementation->settings->quantity()->value();

    for (int i =1; i <= numberPlayersFromSettings; ++i)
    {
        jsonObject.insert("number", QString::number(i));
        jsonObject.insert("isConnected", "");
        jsonObject.insert("points", "0");
        jsonObject.insert("attempts", "0");
        jsonObject.insert("isLeader", "false");

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

int GamePlay::getMaxPoints()
{
    int max = 0;
    QMap<QString, int>::iterator it = implementation->gamePoints.begin();
    for ( ; it != implementation->gamePoints.end(); ++it)
    {
        if ( max <= it.value())
        {
            max = it.value();
        }
    }
    return max;
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
        QString ip;

    //get from tcpcontroller connected clients and for each ip insert "ip" in JsonObject
        QMapIterator<int, QTcpSocket *> i(implementation->tcpController->SClients());
        while (i.hasNext())
        {
    //insert last number of client`s ip in jsonObject
            i.next();
            QString entireIp = i.value()->peerAddress().toString();
            int sizeIP =entireIp.size();

            if( QString(entireIp[sizeIP - 2]) == QString("0") )
            {
                ip = QString(entireIp[sizeIP - 1]);
            }
//=====================================================================================================
            else if( QString(entireIp[sizeIP - 2]) == QString(".") )
            {
                ip = QString(entireIp[sizeIP - 1]);
            }
//=====================================================================================================
            else if ( QString(entireIp[sizeIP - 2]) == QString("1") )
            {
                ip = entireIp.right(2);
            }
            else
            {
                break;
            }

            jsonObject.insert("number", ip);
    //insert true for connected ip in jsonMap
            jsonMap[ip] = true;

        }

        int maxPoints = getMaxPoints();
        QMap<QString, bool>::iterator it = jsonMap.begin();
        for(; it != jsonMap.end(); ++it)
        {
            if(it.value() == false)
            {
                jsonObject.insert("number", it.key());
                jsonObject.insert("isConnected", "");
                jsonObject.insert("points", "0");
                jsonObject.insert("attempts", "0");
                jsonObject.insert("isLeader", "false");
            }
            else if(it.value() == true)
            {
                jsonObject.insert("number", it.key());
                jsonObject.insert("isConnected", "true");
                jsonObject.insert("points", implementation->gamePoints[it.key()]);
                jsonObject.insert("attempts", implementation->gameAttempts[it.key()]);
                if (implementation->gamePoints[it.key()] == maxPoints)
                {
                    jsonObject.insert("isLeader", "true");
                }
                else
                {
                    jsonObject.insert("isLeader", "false");
                }

            }
            returnArray.append(QJsonValue(jsonObject));
        }
        implementation->playersList->update(returnArray);
        qDebug() << "GamePlay::scan done!";
}


bool GamePlay::isAllPlayersConnected()
{
    if ( (implementation->settings->quantity()->value() + 1) == implementation->tcpController->SClients().size() )
    {
        if (!implementation->gameStarted){
            implementation->gameStarted = true;
            auto questionsArray = implementation->databaseControler->findAll("game");
            implementation->questions->update(questionsArray);
        }
        implementation->allPlayerConnected = true;
        return true;
    }
    return false;
}

void GamePlay::clear()
{
    int numberPlayersFromSettings = implementation->settings->quantity()->value();

    QJsonArray resultsArray;
    QJsonObject jsonObject;

    for (int i =1; i <= numberPlayersFromSettings; ++i)
    {
        jsonObject.insert("number", QString::number(i));
        jsonObject.insert("isConnected", "");
        jsonObject.insert("points", "0");
        jsonObject.insert("attempts", "0");

       resultsArray.append(QJsonValue(jsonObject));
    }

    implementation->playersList->update(resultsArray);

    implementation->gamePoints.clear();

    implementation->gameAttempts.clear();

    implementation->allPlayerConnected = false;

    implementation->gameStarted = false;

    implementation->waitAnswer = false;

    implementation->isFirstQuestion = true;

    implementation->nextQuestion =  true;
}


void GamePlay::getMessageFromTCP(const QByteArray& message)
{
    QString qstringMessage = QString::fromUtf8(message);

//Start game
    if( implementation->allPlayerConnected ){

//Question did not asked yet
        if ( !implementation->waitAnswer )
        {
//Check either correct message from tcp client
            if( qstringMessage.trimmed() == "n" || qstringMessage.trimmed() == "a" )
            {
//If question only one
                if( implementation->isFirstQuestion )
                {
                    qDebug() << "FIRST QUESTION";
                    implementation->isFirstQuestion = false;
                    implementation->tcpController->sendMessage("0");
                    implementation->navigationController->goGameQuestionView(implementation->questions->derivedEntities().first());
                    implementation->waitAnswer = true;
                }

//                else if( implementation->inEmtyQuestionList )
//                {
//                    qDebug() << "EmtyQuestion" << implementation->inEmtyQuestionList;
//                    implementation->inEmtyQuestionList = false;
//                    implementation->isFirstQuestion = true;
//                    implementation->navigationController->goGameOverView();
//                    implementation->aDisabled = true;
//                }
//Check either a questions list not emty yet
                else if ( implementation->questions->derivedEntities().size() > 1 )
                {
//Check either the first question in the questions list or message was "a"
                    if ( implementation->isFirstQuestion || (qstringMessage.trimmed() == "a" && !implementation->aDisabled))
                    {
                        implementation->tcpController->sendMessage("0");
                        implementation->navigationController->goGameQuestionView(implementation->questions->derivedEntities().first());
                        implementation->waitAnswer = true;
                    }
                    else
                    {
                        if(!implementation->nextQuestion)
                        {
                            implementation->nextQuestion =  true;
                            implementation->gamePoints[implementation->playerNumber->value()]++;
                            scan();
                            implementation->navigationController->goPlayerWinView(implementation->playerNumber);
                            implementation->aDisabled = true;
                        }
                        else
                        {
//Check either last the question in the questions list
                            if ( implementation->questions->derivedEntities().size() == 1 )
                            {
                                implementation->tcpController->sendMessage("0");
                                implementation->navigationController->goGameQuestionView(implementation->questions->derivedEntities().first());
                                implementation->questions->derivedEntities().removeFirst();
                                implementation->waitAnswer = true;
                                implementation->aDisabled = false;
                            }
                            else
                            {
                                implementation->tcpController->sendMessage("0");
                                implementation->questions->derivedEntities().removeFirst();
                                implementation->navigationController->goGameQuestionView(implementation->questions->derivedEntities().first());
                                implementation->waitAnswer = true;
                                implementation->aDisabled = false;
                            }
                        }
                    }
                }
//The question list emty -  game over
                else
                {
//a from rc
                    if ( qstringMessage.trimmed() == "a" && !implementation->aDisabled)
                    {
                        implementation->tcpController->sendMessage("0");
                        implementation->navigationController->goGameQuestionView(implementation->questions->derivedEntities().first());
                        implementation->waitAnswer = true;
                    }
//n from rc
                    else
                    {
                        implementation->gameStarted = false;
                        implementation->gamePoints[implementation->playerNumber->value()]++;
                        scan();
                        implementation->waitAnswer = false;
                        implementation->navigationController->goEmptyQuestionsListView();
                        implementation->inEmtyQuestionList = true;
                        qDebug() << "SEY INEQ in: " << implementation->inEmtyQuestionList;
                    }
                }

                implementation->isFirstQuestion = false;
            }
        }
//Question asked and message was not "n" or "a app - wait answer
        else if ( qstringMessage.trimmed() != "n" && qstringMessage.trimmed() != "a" && implementation->waitAnswer )
        {
            implementation->playerNumber->setValue( qstringMessage.trimmed() );
            implementation->gameAttempts[implementation->playerNumber->value()]++;
            implementation->navigationController->goGameAnswerView( implementation->playerNumber );
            implementation->waitAnswer = false;
            implementation->nextQuestion = false;
        }
    }
    qDebug() << "Message got: " << message << " FUUUUUU";
}


}}

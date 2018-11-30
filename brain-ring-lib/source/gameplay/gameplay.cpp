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
    bool isEmceeConnected;

//When game starts and waiting clients, this provide last ip broadcast
    bool allIpBroadcasted;

    QMap <QString, int> gamePoints;
    QMap <QString, int> gameAttempts;
    QList<QString> losers;

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

    implementation->isEmceeConnected = false;

    implementation->allIpBroadcasted = false;

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

int GamePlay::getConnectedPlayerNum(QMap<QString, bool> jsonMap)
{
    int returnValue = 0;
    int n = jsonMap.size();

    for(int i = 1; i <= n; ++i)
    {
        if (jsonMap[QString::number(i)] == true)
        {
           returnValue++;
        }
    }
    return returnValue;
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

            if ( entireIp.isEmpty() )
            {
                continue;
            }
            else if( QString(entireIp[sizeIP - 2]) == "0" )
            {
                ip = QString(entireIp[sizeIP - 1]);
            }
            else if ( QString(entireIp[sizeIP - 2]) == "1" )
            {
                ip = entireIp.right(2);
            }
            else
            {
                implementation->isEmceeConnected = true;
                continue;
            }

            jsonObject.insert("number", ip);
    //insert true for connected ip in jsonMap

            jsonMap[ip] = true;

            int connectedPlayerNumber = getConnectedPlayerNum(jsonMap);

//When game starts and waiting clients, this provide last ip broadcast
            if ( implementation->allIpBroadcasted ) continue;
//ip broadcast
            if ( ( !implementation->allPlayerConnected ) && ( ( implementation->settings->quantity()->value() ) >=  connectedPlayerNumber))
            {
                implementation->tcpController->sendMessage(ip);
            }
//When game starts and waiting clients, this provide last ip broadcast
            else if ( implementation->allPlayerConnected )
            {
                implementation->tcpController->sendMessage(ip);
                implementation->allIpBroadcasted = true;
            }
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

bool GamePlay::isEmceeConnected()
{
    return implementation->isEmceeConnected;
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

    implementation->isEmceeConnected = false;

    implementation->gameStarted = false;

    implementation->waitAnswer = false;

    implementation->isFirstQuestion = true;

    implementation->nextQuestion =  true;

    implementation->allIpBroadcasted = false;
}

void GamePlay::gameWithQuestionsAndQuestionIsNotLast(const QString& message)
{
//    qDebug() << "Not first question and question is not last or game without questions";


//a and a permited
    if ( (message.trimmed() == "a" && !implementation->aDisabled) )
    {
//        qDebug() << "+Got a and a permitted";
        implementation->tcpController->sendMessage("0");
        implementation->waitAnswer = true;
//without questions
        if ( implementation->settings->askQuestions()->value() == 0 )
        {
//            qDebug() << "++game without questions";
            Game* emptyGame{nullptr};
            implementation->navigationController->goGameQuestionView(emptyGame);
        }
//with questions
        else
        {
//            qDebug() << "++game with questions";
            implementation->navigationController->goGameQuestionView(implementation->questions->derivedEntities().first());
        }
    }
//not first question and not a
    else
    {
//        qDebug() << "+Got not a or a not permitted or together";
        if(!implementation->nextQuestion)
        {
//            qDebug() << "++not next question";
            implementation->nextQuestion =  true;
            implementation->gamePoints[implementation->playerNumber->value()]++;
            scan();
            implementation->navigationController->goPlayerWinView(implementation->playerNumber);
            implementation->losers.clear();
            implementation->aDisabled = true;
        }
        else
        {
//            qDebug() << "++next question";
//Check either last the question in the questions list

            if ( implementation->questions->derivedEntities().size() == 1 )
            {
//                qDebug() << "+++ last question";
                implementation->tcpController->sendMessage("0");

                if ( implementation->settings->askQuestions()->value() == 0 )
                {
//                    qDebug() << "++++game without questions";
                    Game* emptyGame{nullptr};
                    implementation->navigationController->goGameQuestionView(emptyGame);
                }
                else
                {
//                    qDebug() << "++++game with questions";
                    implementation->navigationController->goGameQuestionView(implementation->questions->derivedEntities().first());
                    implementation->questions->derivedEntities().removeFirst();
                }

                implementation->waitAnswer = true;
                implementation->aDisabled = false;
            }
            else
            {
//                qDebug() << "+++not the last question";
                implementation->tcpController->sendMessage("0");
                implementation->questions->derivedEntities().removeFirst();

                if ( implementation->settings->askQuestions()->value() == 0 )
                {
//                    qDebug() << "++++game without questions";
                    Game* emptyGame{nullptr};
                    implementation->navigationController->goGameQuestionView(emptyGame);
                }
                else
                {
//                    qDebug() << "++++game with questions";
                    implementation->navigationController->goGameQuestionView(implementation->questions->derivedEntities().first());
                }

                implementation->waitAnswer = true;
                implementation->aDisabled = false;
            }
        }
//        qDebug() << "Not First Questions or 'a'";
        implementation->tcpController->SClients();
    }
}

void GamePlay::gameWithoutQuestionsOrQuestionIsLast(const QString &message)
{
//    qDebug() << "++++game without questions";
//a from rc
    if ( message.trimmed() == "a" && !implementation->aDisabled)
    {
        implementation->tcpController->sendMessage("0");

        if ( implementation->settings->askQuestions()->value() == 0 )
        {
            Game* emptyGame{nullptr};
            implementation->navigationController->goGameQuestionView(emptyGame);
        }
        else
        {
            implementation->navigationController->goGameQuestionView(implementation->questions->derivedEntities().first());
        }

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
        implementation->losers.clear();
    }
//    qDebug() << "Not not not First Questions or 'a '";
}

void GamePlay::gotLetterFromTCP(const QString &message)
{

    if (message.isEmpty())
    {
        return;
    }
    else if( message.trimmed() == "n" || message.trimmed() == "a" )
    {
//        qDebug() << "Got n or a";

//First question
        if( implementation->isFirstQuestion )
        {
//            qDebug() << "First question";
            implementation->isFirstQuestion = false;
            implementation->tcpController->sendMessage("0");

    //Without questions
            if ( implementation->settings->askQuestions()->value() == 0 )
            {
//                qDebug() << "+without questions";
                Game* emptyGame{nullptr};
                implementation->navigationController->goGameQuestionView(emptyGame);
                implementation->tcpController->SClients();
            }
    //With questions
            else
            {
//                qDebug() << "+with questions";
                implementation->navigationController->goGameQuestionView(implementation->questions->derivedEntities().first());
//                qDebug() << "First  Questions not empty";
                implementation->tcpController->SClients();
             }

            implementation->waitAnswer = true;
        }

// Not First question
// and
// question is not last or without questions
        else if ( ( implementation->questions->derivedEntities().size() > 1 ) || ( implementation->settings->askQuestions()->value() == 0 ))
        {
            gameWithQuestionsAndQuestionIsNotLast(message);
        }
//The question list empty -  game over
        else
        {
            gameWithoutQuestionsOrQuestionIsLast(message);
        }

        implementation->isFirstQuestion = false;
    }
    return;
}

void GamePlay::gotNumberFromTCP(const QString &message)
{
//    qDebug() << "In number start";
    implementation->tcpController->SClients();
    if (message.isEmpty())
    {
        return;
    }
    else if ( message.trimmed() != "n" && message.trimmed() != "a" && implementation->waitAnswer )
    {
        if ( implementation->losers.contains( message.trimmed() ) )
        {
//            qDebug() << "Contains";
            implementation->tcpController->SClients();
            return;
        }
        implementation->tcpController->sendMessage( message.trimmed() );
        implementation->playerNumber->setValue( message.trimmed() );
        implementation->gameAttempts[implementation->playerNumber->value()]++;
        implementation->navigationController->goGameAnswerView( implementation->playerNumber );
        implementation->waitAnswer = false;
        implementation->nextQuestion = false;
        implementation->losers.push_back(message.trimmed());

//        qDebug() << "In number start HERE..............";
        implementation->tcpController->SClients();

        if (implementation->losers.size() == implementation->settings->quantity()->value())
        {
//            qDebug() << "In clearing";
            implementation->tcpController->SClients();
            implementation->losers.clear();
        }
    }
//qDebug() << "In number end";
implementation->tcpController->SClients();
    return;
}

void GamePlay::gotNextQuestionForce()
{
    implementation->tcpController->sendMessage("0");
    if ( implementation->questions->derivedEntities().size() == 0 )
    {
        implementation->gameStarted = false;
        scan();
        implementation->waitAnswer = false;
        implementation->navigationController->goEmptyQuestionsListView();
        implementation->inEmtyQuestionList = true;
        implementation->losers.clear();
    }
    else if ( implementation->questions->derivedEntities().size() == 1 )
    {
        implementation->navigationController->goGameQuestionView(implementation->questions->derivedEntities().first());
        implementation->questions->derivedEntities().removeFirst();
        implementation->losers.clear();
    }
    else
    {
        implementation->questions->derivedEntities().removeFirst();
        implementation->navigationController->goGameQuestionView(implementation->questions->derivedEntities().first());
        implementation->losers.clear();
    }
}

void GamePlay::getMessageFromTCP(const QByteArray& message)
{
    QString qstringMessage = QString::fromUtf8(message);

//Start game
    if( implementation->allPlayerConnected ){

        if( implementation->waitAnswer && qstringMessage.trimmed() == "f" )
        {
            gotNextQuestionForce();
            return;
        }
//Question did not asked yet
        else if ( !implementation->waitAnswer )
        {
            gotLetterFromTCP(qstringMessage);
        }
//Question asked and message was not "n" or "a app - wait answer
        gotNumberFromTCP(qstringMessage);
    }
}

}}

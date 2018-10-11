#include "tcpclientslist.h"

using namespace br::controllers;
using namespace br::data;

namespace br {
namespace models {

class TCPClientsList::Implementation
{
public:
    Implementation(TCPClientsList* _tcpClientsList, TCPController* _tcpController, Settings* _settings)
        : tcpClientsList(_tcpClientsList)
        , tcpController(_tcpController)
        , settings(_settings)
    {}

    TCPClientsList* tcpClientsList{nullptr};
    TCPController* tcpController{nullptr};
    Settings* settings{nullptr};
    data::EntityCollection<TCPClient>* tcpClients{nullptr};
};

TCPClientsList::TCPClientsList(QObject* parent, TCPController* tcpController, Settings* settings)
    : Entity(parent, "TCPClientsList")
{
    implementation.reset(new Implementation(this, tcpController, settings));
    implementation->tcpClients = static_cast<EntityCollection<TCPClient>*>(addChildCollection(new EntityCollection<TCPClient>(this, "tcp")));


    connect(implementation->tcpClients, &EntityCollection<TCPClient>::collectionChanged, this, &TCPClientsList::tcpClientsListChanged);

    connect(implementation->tcpController, &TCPController::tcpClientArrived, this, &TCPClientsList::scan);



    int playersNumber = implementation->settings->quantity()->value();

    QJsonArray resultsArray;
    QJsonObject jsonObject;

    for (int i =1; i <= playersNumber; ++i)
    {
        jsonObject.insert("number", "");
        jsonObject.insert("ip", QString::number(i));
        jsonObject.insert("isConnected", "");

    resultsArray.append(QJsonValue(jsonObject));

    }

    implementation->tcpClients->update(resultsArray);
//    qDebug() << "Array size: " << QString::number(resultsArray.size());
}

TCPClientsList::~TCPClientsList(){}

QQmlListProperty<TCPClient> TCPClientsList::ui_tcpClients()
{
    scan();
//    qDebug() << "ui_tcpClients" << QString::number(implementation->tcpClients->derivedEntities().size());
    return QQmlListProperty<TCPClient>(this, implementation->tcpClients->derivedEntities());
}

void TCPClientsList::scan()
{
    auto resultsArray = implementation->tcpController->SClients();
//    qDebug() << "TCP client sadfsdas";

    implementation->tcpClients->update(resultsArray);
//    qDebug() << "TCPClientsList::scan ARRAY SIZE: " << QString::number(resultsArray.size());
}

}}

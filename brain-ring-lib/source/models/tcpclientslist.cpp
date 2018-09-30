#include "tcpclientslist.h"

using namespace br::controllers;
using namespace br::data;

namespace br {
namespace models {

class TCPClientsList::Implementation
{
public:
    Implementation(TCPClientsList* _tcpClientsList, TCPController* _tcpController)
        : tcpClientsList(_tcpClientsList)
        , tcpController(_tcpController)
    {}

    TCPClientsList* tcpClientsList{nullptr};
    TCPController* tcpController{nullptr};
    data::EntityCollection<TCPClient>* tcpClients{nullptr};
};

TCPClientsList::TCPClientsList(QObject* parent, TCPController* tcpController)
    : Entity(parent, "TCPClientsList")
{
    qDebug() << "tcp clients list initialized";
    implementation.reset(new Implementation(this, tcpController));
    implementation->tcpClients = static_cast<EntityCollection<TCPClient>*>(addChildCollection(new EntityCollection<TCPClient>(this, "tcp")));


    connect(implementation->tcpClients, &EntityCollection<TCPClient>::collectionChanged, this, &TCPClientsList::tcpClientsListChanged);

    connect(implementation->tcpController, &TCPController::tcpClientArrived, this, &TCPClientsList::scan);

//VARIABLE LATER MAY BE ASSIGN FROM UI//////////////////////////////////////
    int playersNumber = 5;
    QJsonArray resultsArray;
    QJsonObject jsonObject;

    for (int i =1; i <= playersNumber; ++i)
    {
        jsonObject.insert("number", "");
        jsonObject.insert("ip", QString::number(i));
        jsonObject.insert("isConnected", "");

//-DELETE//DELETE//DELETE//DELETE//DELETE//DELETE//DELETE//DELETE//DELETE
//    QJsonDocument doc(jsonObject);
//    QString strJson(doc.toJson(QJsonDocument::Compact));
//    qDebug() << "TCPClientsList with " << strJson << " at " << QString::number(i);
//-DELETE//DELETE//DELETE//DELETE//DELETE//DELETE//DELETE//DELETE//DELETE

    resultsArray.append(QJsonValue(jsonObject));

    }

    implementation->tcpClients->update(resultsArray);
}

TCPClientsList::~TCPClientsList(){}

QQmlListProperty<TCPClient> TCPClientsList::ui_tcpClients()
{
    return QQmlListProperty<TCPClient>(this, implementation->tcpClients->derivedEntities());
}

void TCPClientsList::scan()
{
    auto resultsArray = implementation->tcpController->SClients();

    implementation->tcpClients->update(resultsArray);
    qDebug() << "TCPClientsList::scan ARRAY SIZE: " << QString::number(resultsArray.size());
}

}}

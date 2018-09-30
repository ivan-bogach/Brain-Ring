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

//    this->scan();

//    auto resultsArray = implementation->tcpController->SClients();
//    implementation->tcpClients->update(resultsArray);
}

TCPClientsList::~TCPClientsList(){}

QQmlListProperty<TCPClient> TCPClientsList::ui_tcpClients()
{
    return QQmlListProperty<TCPClient>(this, implementation->tcpClients->derivedEntities());
}

void TCPClientsList::scan()
{
    qDebug() << "SIGNAL RECEIVED";
    auto resultsArray = implementation->tcpController->SClients();
    implementation->tcpClients->update(resultsArray);
    qDebug() << "TCPClientsList::scan ARRAY SIZE: " << QString::number(resultsArray.size());
}

}}

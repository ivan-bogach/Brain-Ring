#include "tcp-controller.h"

namespace br {
namespace controllers {

class TCPController::Implementation
{
public:
    Implementation(TCPController* _tcpController, models::Settings* _settings, IDatabaseController* _databaseController, gameplay::Player* _newPlayer)
        : tcpController(_tcpController)
        , settings(_settings)
        , databaseController(_databaseController)
        , newPlayer(_newPlayer)
    {

    }
    TCPController* tcpController{nullptr};
    models::Settings* settings{nullptr};
    IDatabaseController* databaseController{nullptr};
    gameplay::Player* newPlayer{nullptr};

    int serverStatus;
    QMap<int, QTcpSocket *> SClients;
};

TCPController::TCPController(QObject *parent, models::Settings* settings, IDatabaseController* databaseController, gameplay::Player *newPlayer)
    :QObject(parent)
{
    implementation.reset(new Implementation(this, settings, databaseController, newPlayer));
}

TCPController::~TCPController(){}

QMap<int, QTcpSocket *> TCPController::SClients()
{
    return implementation->SClients;
}

void TCPController::startServer()
{
    qDebug() << "TCP CONTROLLER: startServer...";

    tcpServer = new QTcpServer(this);

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newClient()));

    if (!tcpServer->listen(QHostAddress::Any, 3337)  && implementation->serverStatus == 0)
    {
        qDebug()  <<QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
    }
    else
    {
        implementation->serverStatus = 1;
    }
}

void TCPController::stopServer()
{
//    qDebug() << "TCP CONTROLLER: stopServer...";

    if (implementation->serverStatus == 1)
    {
        foreach (int i, implementation->SClients.keys()) {
          implementation->SClients[i]->close();
          implementation->SClients.remove(i);
        }

        tcpServer->close();
        qDebug() << QString::fromUtf8("TCP CONTROLLER: Server stoped!");
        implementation->serverStatus = 0;
    }
}

void TCPController::newClient()
{
    if (implementation->serverStatus == 1)
    {

        QTcpSocket* clientSocket = tcpServer->nextPendingConnection();

        int idUserSocket = clientSocket->socketDescriptor();

//Writing back client's ip last number
//        QString entireIp = clientSocket->peerAddress().toString();
//        int sizeIP =entireIp.size();
//        QString ip = QString(entireIp[sizeIP - 1]);
//        QString ip = entireIp.right(2);
//        clientSocket->write(ip.toUtf8());

        implementation->SClients[idUserSocket] = clientSocket;

        connect(implementation->SClients[idUserSocket], SIGNAL(readyRead()), this, SLOT(slotReadClient()));

        emit tcpClientArrived();
    }
}

void TCPController::sendMessage(const QString &message)
{
    foreach (int i, implementation->SClients.keys()) {
        implementation->SClients[i]->write(message.toUtf8());
    }
}

void TCPController::slotReadClient()
{
    QByteArray returnValue;

    QTcpSocket* clientSocket = (QTcpSocket*)sender();

    returnValue = clientSocket->readAll();

//    qDebug()<< "MESSAGE:" << returnValue;

//    return returnValue;
    emit messageArrived(returnValue);
}

}
}

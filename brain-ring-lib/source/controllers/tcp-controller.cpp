#include "tcp-controller.h"

namespace br {
namespace controllers {

class TCPController::Implementation
{
public:
    Implementation(TCPController* _tcpController, models::Settings* _settings)
        : tcpController(_tcpController)
        , settings(_settings)
    {

    }
    TCPController* tcpController{nullptr};
    models::Settings* settings{nullptr};
    int serverStatus;
    QMap<int, QTcpSocket *> SClients;
};

TCPController::TCPController(QObject *parent, models::Settings* settings)
    :QObject(parent)
{
    implementation.reset(new Implementation(this, settings));
}

TCPController::~TCPController(){}

QJsonArray TCPController::SClients()
{
//    qDebug() << "HERE";

    int clientsNumber = implementation->settings->quantity()->value();
//    qDebug() << "TCP controller clientsNumber: " << clientsNumber;

    QMap<QString, bool> jsonMap;
    for(int i = 1; i <= clientsNumber; ++i)
    {
        jsonMap[QString::number(i)] = false;
    }

    QJsonArray returnArray;
    QJsonObject jsonObject;
    QMapIterator<int, QTcpSocket *> i(implementation->SClients);
    while (i.hasNext())
    {
        i.next();
        QString entireIp = i.value()->peerAddress().toString();
        int sizeIP =entireIp.size();
        QString ip = QString(entireIp[sizeIP - 1]);


        jsonObject.insert("ip", ip);

        jsonMap[ip] = true;
    }

    QMap<QString, bool>::iterator it = jsonMap.begin();
    for(; it != jsonMap.end(); ++it)
    {
        if(it.value() == false)
        {
            jsonObject.insert("ip", it.key());
            jsonObject.insert("isConnected", "");
        }
        else if(it.value() == true)
        {
            jsonObject.insert("ip", it.key());
            jsonObject.insert("isConnected", "true");

        }
        returnArray.append(QJsonValue(jsonObject));
    }

    return returnArray;
}

void TCPController::startServer()
{
//    qDebug() << "TCP CONTROLLER: startServer...";

    tcpServer = new QTcpServer(this);

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newClient()));

    if (!tcpServer->listen(QHostAddress::Any, 3337)  && implementation->serverStatus == 0)
    {
        qDebug()  <<QObject::tr("Unable to start the server: %1.").arg(tcpServer->errorString());
    }
    else
    {
        implementation->serverStatus = 1;
//        qDebug() << tcpServer->isListening() << "TCP CONTROLLER:  TCPSocket listen on port";
//        qDebug() << tcpServer->serverAddress().toString() << "Address";
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
//    qDebug() << "New Client";
    if (implementation->serverStatus == 1)
    {

        QTcpSocket* clientSocket = tcpServer->nextPendingConnection();

        int idUserSocket = clientSocket->socketDescriptor();

        implementation->SClients[idUserSocket] = clientSocket;

        connect(implementation->SClients[idUserSocket], SIGNAL(readyRead()), this, SLOT(slotReadClient()));

        emit tcpClientArrived();

//        qDebug()<< "NEW";

//Writing back client's ip last number
        QString entireIp = clientSocket->peerAddress().toString();
        int sizeIP =entireIp.size();
        QString ip = QString(entireIp[sizeIP - 1]);
        clientSocket->write(ip.toUtf8());
    }
}

QByteArray TCPController::slotReadClient()
{
    QByteArray returnValue;

    QTcpSocket* clientSocket = (QTcpSocket*)sender();

    returnValue = clientSocket->readAll();

    return returnValue;
}

}
}

#include "tcp-controller.h"

namespace br {
namespace controllers {

class TCPController::Implementation
{
public:
    Implementation(TCPController* _tcpController)
        : tcpController(_tcpController)
    {

    }
    TCPController* tcpController{nullptr};
    int serverStatus;
    QMap<int, QTcpSocket *> SClients;
//    models::TCPClientsList* tcpClientsList{nullptr};
};

TCPController::TCPController(QObject *parent)
    :QObject(parent)
{
    implementation.reset(new Implementation(this));
}

TCPController::~TCPController(){}

QJsonArray TCPController::SClients()
{
    qDebug() << "I`m here!!!!!!!!!!!!!!!!!!!!";

 //VARIABLE LATER MAY BE ASSIGN FROM UI//////////////////////////////////////
    int clientsNumber = 5;
 //-/////////////////////////////////////////////////////////////////////////
    QMap<QString, bool> jsonMap;
    for(int i = 1; i <= clientsNumber; ++i)
    {
        jsonMap[QString::number(i)] = false;
    }

    qDebug() << "At first jsonMap has " << QString::number(jsonMap.size()) << " elements";


    QJsonArray returnArray;
    QJsonObject jsonObject;
    QMapIterator<int, QTcpSocket *> i(implementation->SClients);
    while (i.hasNext())
    {
        i.next();


        jsonObject.insert("number", i.key());

        QString entireIp = i.value()->peerAddress().toString();
        int sizeIP =entireIp.size();
        QString ip = QString(entireIp[sizeIP - 1]);


        jsonObject.insert("ip", ip);

        jsonMap[ip] = true;


        jsonObject.insert("isConnected", QString("true"));

        qDebug() << "TCPController ip: " << i.value()->peerAddress().toString();
        qDebug()  << "TCPController num: " << i.key();

        returnArray.append(QJsonValue(jsonObject));
    }

    qDebug() << "And then jsonMap has " << QString::number(jsonMap.size()) << " elements";

    QMap<QString, bool>::iterator it = jsonMap.begin();
    for(; it != jsonMap.end(); ++it)
    {
        if (it.value() == false)
        {
            jsonObject.insert("number", "");
            jsonObject.insert("ip", it.key());
            jsonObject.insert("isConnected", "");
            returnArray.append(QJsonValue(jsonObject));
        }
    }

    return returnArray;
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
        qDebug() << tcpServer->isListening() << "TCP CONTROLLER:  TCPSocket listen on port";
        qDebug() << tcpServer->serverAddress().toString() << "Address";
    }
}

void TCPController::stopServer()
{
    qDebug() << "TCP CONTROLLER: stopServer...";

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

        implementation->SClients[idUserSocket] = clientSocket;

        connect(implementation->SClients[idUserSocket], SIGNAL(readyRead()), this, SLOT(slotReadClient()));

        emit tcpClientArrived();

        qDebug() << QString::fromUtf8("New connection arrived: ") << clientSocket->peerAddress().toString();
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

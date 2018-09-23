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
    QTcpServer* tcpServer;
    int serverStatus;
    QMap<int, QTcpSocket *> SClients;
};

TCPController::TCPController(QObject *parent)
    :QObject(parent)
{
    implementation.reset(new Implementation(this));
}

TCPController::~TCPController(){}

void TCPController::startServer()
{
    connect(implementation->tcpServer, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if (!implementation->tcpServer->listen(QHostAddress::Any, 3337))
    {
        qDebug()  <<QObject::tr("Unable to start the server: %1.").arg(implementation->tcpServer->errorString());
    }
    else
    {
        implementation->serverStatus = 1;
        qDebug() <<implementation->tcpServer->isListening() << "TCPSocket listen on port";
    }
}

void TCPController::stopServer()
{
    if (implementation->serverStatus == 1)
    {
        foreach (int i, implementation->SClients.keys()) {
          implementation->SClients[i]->close();
          implementation->SClients.remove(i);
        }
        implementation->tcpServer->close();
         qDebug() << QString::fromUtf8("Server stoped!");
         implementation->serverStatus = 0;
    }
}

void TCPController::newConnection()
{
    if (implementation->serverStatus == 1)
    {
        qDebug() << QString::fromUtf8("New connection arrived!");

        QTcpSocket* clientSocket = implementation->tcpServer->nextPendingConnection();

        int idUserSocket = clientSocket->socketDescriptor();

        implementation->SClients[idUserSocket] = clientSocket;

        connect(implementation->SClients[idUserSocket], SIGNAL(readyRead()), this, SLOT(slotReadClient()));
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

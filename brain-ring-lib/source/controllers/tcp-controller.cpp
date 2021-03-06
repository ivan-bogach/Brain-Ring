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
};

TCPController::TCPController(QObject *parent)
    :QObject(parent)
{
    implementation.reset(new Implementation(this));
}

TCPController::~TCPController(){}

void TCPController::startServer()
{
    qDebug() << "TCP CONTROLLER: startServer...";

    tcpServer = new QTcpServer(this);

    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(newClient()));

    qDebug() << "TCP CONTROLLER: startServer after connect...";

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
        qDebug() << QString::fromUtf8("New connection arrived!");

        QTcpSocket* clientSocket = tcpServer->nextPendingConnection();

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

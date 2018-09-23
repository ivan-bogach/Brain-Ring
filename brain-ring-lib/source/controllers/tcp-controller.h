#ifndef TCPCONTROLLER_H
#define TCPCONTROLLER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QByteArray>

#include <QObject>
#include <QScopedPointer>

#include <brain-ring-lib_global.h>

namespace br {
namespace controllers {


class BRAINRINGLIBSHARED_EXPORT TCPController : public QObject
{
    Q_OBJECT
public:
    explicit TCPController(QObject* parent = nullptr);
    ~TCPController();

public slots:
    void startServer();
    void stopServer();
    void newConnection();
    QByteArray slotReadClient();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}
#endif // TCPCONTROLLER_H

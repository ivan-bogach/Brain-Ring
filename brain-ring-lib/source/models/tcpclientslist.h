#ifndef TCPCLIENTSLIST_H
#define TCPCLIENTSLIST_H

#include <QObject>
#include <QScopedPointer>
#include <QtQml/QQmlListProperty>
#include <QJsonDocument>

#include <brain-ring-lib_global.h>
#include <controllers/tcp-controller.h>
#include <data/entity.h>
#include <data/entity-collection.h>
#include <models/tcpclient.h>
#include <models/settings.h>

namespace br {
namespace models {


class BRAINRINGLIBSHARED_EXPORT TCPClientsList : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(QQmlListProperty<br::models::TCPClient> ui_tcpClients READ ui_tcpClients NOTIFY tcpClientsListChanged)
public:
    TCPClientsList(QObject* parent = nullptr, controllers::TCPController* tcpController = nullptr, models::Settings* settings = nullptr);
    ~TCPClientsList();

    QQmlListProperty<TCPClient> ui_tcpClients();
    void scan();

signals:
    void tcpClientsListChanged();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};


}}
#endif // TCPCLIENTSLIST_H

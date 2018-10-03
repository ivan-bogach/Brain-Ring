#include "tcpclient.h"

using namespace br::data;

namespace br {
namespace models {

TCPClient::TCPClient(QObject* parent)
    : Entity(parent, "TCP client")
{
    ip = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "ip", "ip")));
    isConnected = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "isConnected", "isConnected")));
}

TCPClient::TCPClient(QObject *parent, const QJsonObject &json)
    : TCPClient(parent)
{
    update(json);
}

}}

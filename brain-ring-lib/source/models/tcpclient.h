#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>

#include "brain-ring-lib_global.h"
#include <data/entity.h>
#include <data/stringdecorator.h>


namespace br {
namespace models {


class BRAINRINGLIBSHARED_EXPORT TCPClient : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(br::data::StringDecorator* ui_ip MEMBER ip CONSTANT)

public:
    explicit TCPClient(QObject* parent = nullptr);
    TCPClient(QObject *parent, const QJsonObject& json);

    data::StringDecorator* ip{nullptr};
};

}
}
#endif // TCPCLIENT_H

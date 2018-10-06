#include "tcpclientcommand.h"

namespace br {
namespace framework {

class TCPClientCommand::Implementation
{
public:
    Implementation(const QString& _number, const QString& _icon)
        : number(_number)
        , icon(_icon)
    {}

    QString number;
    QString icon;
};

TCPClientCommand::TCPClientCommand(QObject* parent, const QString& number, const QString& icon)
    : QObject(parent)
{
    implementation.reset(new Implementation(number, icon));
}

TCPClientCommand::~TCPClientCommand(){}

const QString& TCPClientCommand::icon() const
{
    return implementation->icon;
}

const QString& TCPClientCommand::number() const
{
    return implementation->number;
}

}
}

#include "command.h"

namespace br {
namespace framework {

class Command::Implementation
{
public:
    Implementation(const QString& _icon, const QString& _description, std::function<bool()> _canExecute)
        : icon(_icon)
        , description(_description)
        , canExecute(_canExecute)
    {}

    QString icon;
    QString description;
    std::function<bool()> canExecute;
};

Command::Command(QObject *parent, const QString& icon, const QString& description, std::function<bool()> canExecute)
    : QObject(parent)
{
    implementation.reset(new Implementation(icon, description, canExecute));
}

Command::~Command() {}

const QString& Command::icon() const
{
    return implementation->icon;
}

const QString& Command::description() const
{
    return implementation->description;
}

bool Command::canExecute() const
{
    return implementation->canExecute();
}

}
}

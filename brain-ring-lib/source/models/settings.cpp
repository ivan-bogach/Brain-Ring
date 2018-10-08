#include "settings.h"

using namespace br::data;

namespace br {
namespace models {



Settings::Settings(QObject* parent)
    : Entity(parent, "settings")
{
    quantity = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "quantity", "Количество игроков")));
    askQuestions = static_cast<IntDecorator*>(addDataItem(new IntDecorator(this, "Ask Questions?", "Ask questions?")));
}

Settings::Settings(QObject* parent, const QJsonObject& json)
    :Settings(parent)
{
    update(json);
}

}}

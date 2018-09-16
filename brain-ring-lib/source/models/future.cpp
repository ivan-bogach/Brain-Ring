#include "future.h"

using namespace br::data;

namespace br {
namespace models {


Future::Future(QObject *parent)
    :Entity(parent, "future")
{
    startAt = static_cast<DateTimeDecorator*>(addDataItem(new DateTimeDecorator(this, "startAt", "Начало")));
    notes = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "notes", "Заметки")));
}

Future::Future(QObject* parent, const QJsonObject& json)
    : Future(parent)
{
    update(json);
}

}
}

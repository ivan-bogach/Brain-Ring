#include "info.h"

using namespace br::data;
namespace br {
namespace models {


Info::Info(QObject* parent)
    :Entity(parent, "info")
{
    building = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "building", "Город")));
    street = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "street", "Дом")));
    city = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "city", "Улица")));

}

Info::Info(QObject* parent, const QJsonObject& json)
    :Info(parent)
{
    update(json);
}

QString Info::fullAddress() const
{
    return "Город " + city->value() + ", улица " + street->value() + ", дом " + building->value() + ".";
}

}
}

#include "player.h"

using namespace br::data;


namespace br {
namespace gameplay {

Player::Player(QObject* parent)
    : Entity(parent, "player")
{
  number = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "number", "Номер")));
  points = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "points", "Очки")));
  isConnected = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "isConnected", "Подключен")));
}

Player::Player(QObject* parent, const QJsonObject &json)
    : Player(parent)
{
    update(json);
}

}
}

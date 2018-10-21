#include "player.h"

using namespace br::data;


namespace br {
namespace gameplay {

Player::Player(QObject* parent)
    : Entity(parent, "player")
{
  number = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "number", "Номер")));
  points = static_cast<IntDecorator*>(addDataItem(new IntDecorator(this, "points", "Очки")));
  attempts = static_cast<IntDecorator*>(addDataItem(new IntDecorator(this, "attempts", "Попытки")));
  isConnected = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "isConnected", "Подключен")));
  isLeader = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "isLeader", "Лидер")));
}

Player::Player(QObject* parent, const QJsonObject &json)
    : Player(parent)
{
    update(json);
}

}
}

#include "player.h"

using namespace br::data;
using namespace br::models;

namespace br {
namespace gameplay {

class Player::Implementation
{
public:
    Implementation(Player* _player)
        : player(_player)
    {}

    Player* player{nullptr};
    IntDecorator* number{nullptr};
    StringDecorator* points{nullptr};
};


Player::Player(QObject* parent)
    : Entity(parent, "player")
{
    implementation.reset(new Implementation(this));

    implementation->number = static_cast<IntDecorator*>(addDataItem(new IntDecorator(this, "number", "Номер")));
    implementation->points = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "points", "Очки")));
}

Player::Player(QObject* parent, const QJsonObject &json)
    : Player(parent)
{
    update(json);
}

Player::~Player(){}

IntDecorator *Player::number()
{
    return implementation->number;
}

StringDecorator* Player::points()
{
    return implementation->points;
}

void Player::clear()
{
    implementation->number->setValue(0);
    implementation->points->setValue("");
}

}
}

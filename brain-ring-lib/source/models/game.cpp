#include "game.h"
//#include <QDebug>

using namespace br::data;

namespace br {
namespace models {

class Game::Implementation
{
public:
    Implementation(Game* _game)
        : game(_game)
    {}

    Game* game{nullptr};
    data::StringDecorator* number{nullptr};
    data::StringDecorator * text{nullptr};
};

Game::Game(QObject* parent)
    : Entity(parent, "game")
{
    implementation.reset(new Implementation(this));

    implementation->number = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "num", "Номер")));
    implementation->text = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "text", "Текст")));
}

Game::Game(QObject *parent, const QJsonObject &json)
    :Game(parent)
{
    update(json);
}

Game::~Game(){}

StringDecorator* Game::number()
{
    return implementation->number;
}

StringDecorator* Game::text()
{
    return implementation->text;
}

void Game::clear()
{
    implementation->number->setValue("");
    implementation->text->setValue("");
}

}
}

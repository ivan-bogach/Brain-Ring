#include "game.h"
#include <QDebug>

using namespace br::data;

namespace br {
namespace models {


Game::Game(QObject* parent)
    : Entity(parent, "game")
{
    number = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "num", "Номер")));
    text = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "text", "Текст")));
}

Game::Game(QObject *parent, const QJsonObject &json)
    :Game(parent)
{
    update(json);
}

const QString& Game::num() const
{
    return this->number->value();
}

void Game::clear()
{
    this->number->setValue("");
    this->text->setValue("");
}

}
}

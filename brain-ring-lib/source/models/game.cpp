#include "game.h"

using namespace br::data;

namespace br {
namespace models {

Game::Game(QObject* parent)
    : Entity(parent, "game")
{
    questions = static_cast<EntityCollection<Question>*>(addChildCollection(new EntityCollection<Question>(this, "questions")));
    name = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "name", "Имя")));
}

Game::Game(QObject *parent, const QJsonObject &json)
    : Game(parent)
{
    update(json);
}

QQmlListProperty<Question> Game::ui_questions()
{
    return QQmlListProperty<Question>(this, questions->derivedEntities());
}

}
}

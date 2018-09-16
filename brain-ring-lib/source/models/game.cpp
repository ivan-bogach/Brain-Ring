#include "game.h"

using namespace br::data;

namespace br {
namespace models {


Game::Game(QObject* parent)
    : Entity(parent, "game")
{
//std::map<QString, DataDecorator*> dataDecorators
    reference = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "reference", "Game Ref")));
    name = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "name", "Имя")));

//std::map<QString, Entity*> childEntities
    supplyInfo = static_cast<Info*>(addChild(new Info(this), "supplyInfo"));

//std::map<QString, EntityCollectionBase*> childCollections;
    futures = static_cast<EntityCollection<Future>*>(addChildCollection(new EntityCollection<Future>(this, "futures")));
    questions = static_cast<EntityCollection<Question>*>(addChildCollection(new EntityCollection<Question>(this, "questions")));
}

Game::Game(QObject *parent, const QJsonObject &json)
    :Game(parent)
{
    update(json);
}


QQmlListProperty<Future> Game::ui_futures()
{
    return QQmlListProperty<Future>(this, futures->derivedEntities());
}

QQmlListProperty<Question> Game::ui_questions()
{
    return QQmlListProperty<Question>(this, questions->derivedEntities());
}

}
}

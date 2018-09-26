#ifndef ENTITY_H
#define ENTITY_H

#include <map>

#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QScopedPointer>

#include <brain-ring-lib_global.h>
#include <data/datadecorator.h>
#include <data/stringdecorator.h>
#include <data/entity-collection.h>

namespace br {
namespace data {

class BRAINRINGLIBSHARED_EXPORT Entity : public QObject
{
    Q_OBJECT

public:
    Entity(QObject* parent = nullptr, const QString& key = "SomeItemKey");
    Entity(QObject *parent, const QString &key, const QJsonObject& jsonObject);
    virtual ~Entity();

public:

//will be used in JSON serialization
    const QString& key() const;

//to instantiate an	entity from JSON
    void update(const QJsonObject& jsonObject);
    QJsonObject toJson() const;

    EntityCollectionBase* addChildCollection(EntityCollectionBase* entityCollection);

signals:
    void childEntitiesChanged();
    void childCollectionsChanged(const QString& collectionKey);
    void dataDecoratorsChanged();

protected:
    Entity* addChild(Entity* entity, const QString& key);
    DataDecorator* addDataItem(DataDecorator* dataDecorator);

protected:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}
#endif // ENTITY_H

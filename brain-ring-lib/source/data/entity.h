#ifndef ENTITY_H
#define ENTITY_H

#include <map>

#include <QObject>
#include <QScopedPointer>

#include <brain-ring-lib_global.h>
#include <data/datadecorator.h>
#include <data/entity-collection.h>

namespace br {
namespace data {

class BRAINRINGLIBSHARED_EXPORT Entity : public QObject
{
    Q_OBJECT
public:
    Entity(QObject* parent = nullptr, const QString& key = "SomeEntityKey");
    Entity(QObject* parent, const QString& key, const QJsonObject& jsonObject);
    virtual ~Entity();

    const QString& key() const;
    QJsonObject toJson() const;
    void update(const QJsonObject& jsonObject);

signals:
    void childCollectionsChanged(const QString& collectionKey);
    void childEntitiesChanged();
    void dataDecoratorsChanged();

protected:
    Entity* addChild(Entity* entity, const QString& key);
    DataDecorator* addDataItem(DataDecorator* dataDecorator);
    EntityCollectionBase* addChildCollection(EntityCollectionBase* entityCollection);

protected:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}}

#endif

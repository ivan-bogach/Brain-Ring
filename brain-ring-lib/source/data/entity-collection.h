#ifndef ENTITYCOLLECTION
#define ENTITYCOLLECTION

#include <QObject>
#include <QJsonArray>
#include <QJsonValue>

#include <brain-ring-lib_global.h>

namespace br {
namespace data {
class Entity;

//class does nothing more than inheriting from QObject - gives access to all goodness such as object ownership and signals
//required because classes deriving directly from QObject cannot be	templated
class BRAINRINGLIBSHARED_EXPORT EntityCollectionObject : public QObject
{
    Q_OBJECT
public:
    EntityCollectionObject(QObject* _parent = nullptr) : QObject(_parent) {}
    virtual ~EntityCollectionObject() {}

signals:
    void collectionChanged();
};

//UI needs Qa List for access all the properties specific to a game/
//Entity class needs a vector of base types Entity* so that it can iterate
//its collection without caring exactly which type it is dealing with.
class EntityCollectionBase : public EntityCollectionObject
{
public:
    EntityCollectionBase(QObject* parent = nullptr, const QString& key = "SomeCollectionKey")
        : EntityCollectionObject(parent)
        , key(key)
    {}

    virtual ~EntityCollectionBase() {}

    QString getKey() const
    {
        return key;
    }

    virtual void clear() = 0;

    virtual void update(const QJsonArray& json) = 0;

//access to	the	base interface
    virtual std::vector<Entity*> baseEntities() = 0;

//a	collection of the derived type
    template <class T>
    QList<T*>& derivedEntities();

    template <class T>
    T* addEntity(T* entity);

private:
    QString key;
};


//full template class with collection of derived types and implement all methods, except
//addEntity and derivedEntities
template <typename T>
class EntityCollection : public EntityCollectionBase
{
public:
    EntityCollection(QObject* parent = nullptr, const QString& key = "SomeCollectionKey")
        : EntityCollectionBase(parent, key)
    {}
    ~EntityCollection() {}

    void clear() override
    {
        for (auto entity : collection)
        {
            entity->deleteLater();
        }
        collection.clear();
    }

    void update(const QJsonArray& jsonArray) override
    {
        clear();
        for(const QJsonValue& jsonValue : jsonArray)
        {
            addEntity(new T(this, jsonValue.toObject()));
        }
    }

//creating a new vector on request and populating it with all the items in the collection
    std::vector<Entity*> baseEntities() override
    {
        std::vector<Entity*> returnValue;
        for(T* entity : collection)
        {
            returnValue.push_back(entity);
        }
        return returnValue;
    }

//returns the collection
    QList<T*>& derivedEntities()
    {
        return collection;
    }


//add an instance of a derived class to the collection
    T* addEntity(T* entity)
    {
        if(!collection.contains(entity))
        {
            collection.append(entity);
            EntityCollectionObject::collectionChanged();
        }
        return entity;
    }

private:
    QList<T*> collection;
};

template <class T>
QList<T*>& EntityCollectionBase::derivedEntities()
{
    return dynamic_cast<const EntityCollection<T>&>(*this).derivedEntities();
}

template <class T>
T* EntityCollectionBase::addEntity(T* entity)
{
    return dynamic_cast<const EntityCollection<T>&>(*this).addEntity(entity);
}



}
}

#endif // ENTITYCOLLECTION


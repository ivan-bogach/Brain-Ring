#ifndef ENTITYCOLLECTION_H
#define ENTITYCOLLECTION_H

#include <QObject>
//#include <QDebug>
#include <QJsonArray>
#include<QJsonValue>

//..........................................................................................
#include <QJsonDocument>
//..........................................................................................

#include <brain-ring-lib_global.h>

namespace br {
namespace data {

class Entity;

class BRAINRINGLIBSHARED_EXPORT EntityCollectionObject : public QObject
{
    Q_OBJECT
public:
    EntityCollectionObject(QObject* _parent = nullptr)
        :QObject(_parent)
    {}
    virtual ~EntityCollectionObject(){}

signals:
    void collectionChanged();
};

class EntityCollectionBase : public EntityCollectionObject
{
public:
    EntityCollectionBase(QObject* parent = nullptr, const QString& key = "SomeCollectionKye")
        : EntityCollectionObject(parent)
        , key(key)
    {}
    virtual ~EntityCollectionBase(){}

    QString getKey() const{
        return key;
    }
    virtual void clear() = 0;
    virtual void update(const QJsonArray& json) = 0;

//access to the base interface
    virtual std::vector<Entity*> baseEntities() = 0;

//collection of derrived types
    template<class T>
    QList<T*>& derivedEntities();

    template<class T>
    T* addEntity(T* entity);

private:
    QString key;
};

template<typename T>

class EntityCollection : public EntityCollectionBase
{
public:
    EntityCollection(QObject* parent = nullptr, const QString& key = "SomECOllextionKey")
        :EntityCollectionBase(parent, key)
    {}
    ~EntityCollection(){}

//empties the collection and tidies up the memory;
    void clear() override
    {
        for(auto entity : collection)
        {
            entity->deleteLater();
        }

// void QList::clear() - Removes all items from the list.
        collection.clear();
    }


    void update(const QJsonArray& jsonArray) override
    {
        clear();
        for(const QJsonValue& jsonValue : jsonArray)
        {
            addEntity(new T(this, jsonValue.toObject()));
        }
//..........................................................................................
        QJsonDocument jsonDocument;
        jsonDocument.setArray(jsonArray);
//        qDebug() << "entity-collection update entity collection with: " << jsonDocument.toJson();
//..........................................................................................
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


    QList<T*>& derivedEntities()
    {
        return collection;
    }

    T* addEntity(T* entity)
    {
        if(!collection.contains(entity))
        {
            collection.append(entity);
//            qDebug() << "collectionChanged signal from addEntity";
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

#endif // ENTITYCOLLECTION_H

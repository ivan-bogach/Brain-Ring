#ifndef DATADECORATOR_H
#define DATADECORATOR_H

#include <QJsonObject>
#include <QJsonValue>
#include <QObject>
#include <QScopedPointer>

#include <brain-ring-lib_global.h>

namespace br {
namespace data {

class Entity;

class BRAINRINGLIBSHARED_EXPORT DataDecorator : public QObject
{
    Q_OBJECT
public:
// as DataDecorator inherited from QObject, we want to receive a pointer to a parent in our constructor.
// and also all data items will be children of entity which will itself be derived from QObject.
    DataDecorator(Entity* parent = nullptr, const QString& key = "Some item key", const QString& label = "");
// virtual destructor because this is an abstract base class.
    virtual ~DataDecorator();

    const QString& key() const;
    const QString& label() const;

    Entity* parentEntity();

    virtual QJsonValue jsonValue() const = 0;
    virtual void update(const QJsonObject& jsonObject) = 0;

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}

#endif // DATADECORATOR_H

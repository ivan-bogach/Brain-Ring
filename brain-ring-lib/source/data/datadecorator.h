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
    Q_PROPERTY(QString ui_label READ label CONSTANT)

public:
    DataDecorator(Entity* parent = nullptr, const QString& key = "SomeItemKey", const QString& label = "");
    virtual ~DataDecorator();

//will be used when serializing to and from JSON
    const QString& key() const;

//UI will use to display descriptive text
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

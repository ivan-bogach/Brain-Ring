#include "stringdecorator.h"

#include <QVariant>

namespace br {
namespace data {

class StringDecorator::Implementation
{
public:
    Implementation(StringDecorator* _stringDecorator, const QString& _value)
        : stringDecorator(_stringDecorator),
          value(_value)
    {
    }

    StringDecorator* stringDecorator{nullptr};
    QString value;
};

StringDecorator::StringDecorator(Entity* parentEntity, const QString& key, const QString& label, const QString& value)
    :DataDecorator(parentEntity, key, label)
{
    implementation.reset(new Implementation(this, value));
}

StringDecorator::~StringDecorator(){}

const QString& StringDecorator::value() const
{
//    qDebug() << "String Decorator: " << implementation->value;
    return implementation->value;
}

StringDecorator& StringDecorator::setValue(const QString &value)
{
    if(value != implementation->value)
    {
        implementation->value = value;
        emit valueChanged();
    }

//returning a reference to self (*this) enables method chaining: myName.setValue("nhn").setSomeProperty(123)
    return *this;
}

QJsonValue StringDecorator::jsonValue() const
{
    return QJsonValue::fromVariant(QVariant(implementation->value));
}

void StringDecorator::update(const QJsonObject& _jsonObject)
{
    if(_jsonObject.contains(key()))
    {
//QJsonValue plugged into the parent Entity JSON object using the key from the DataDecorator base class.
        setValue(_jsonObject.value(key()).toString());
    }
    else
    {
        setValue("");
    }


}

}
}

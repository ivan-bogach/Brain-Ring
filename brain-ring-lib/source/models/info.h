#ifndef INFO_H
#define INFO_H

#include <QObject>
#include <QJsonObject>

#include<brain-ring-lib_global.h>
#include <data/stringdecorator.h>
#include <data/entity.h>

namespace br {
namespace models {


class BRAINRINGLIBSHARED_EXPORT Info : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(br::data::StringDecorator* ui_building MEMBER building CONSTANT)
    Q_PROPERTY(br::data::StringDecorator* ui_street MEMBER street CONSTANT)
    Q_PROPERTY(br::data::StringDecorator* ui_city MEMBER city CONSTANT)
    Q_PROPERTY(QString ui_fullAddress READ fullAddress CONSTANT)

public:
    explicit Info(QObject* parent = nullptr);
    Info(QObject *parent, const QJsonObject& json);

    data::StringDecorator* building{nullptr};
    data::StringDecorator* street{nullptr};
    data::StringDecorator* city{nullptr};

    QString fullAddress() const;
};

}
}

#endif // INFO_H

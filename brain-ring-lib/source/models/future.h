#ifndef FUTURE_H
#define FUTURE_H

#include <QObject>

#include <brain-ring-lib_global.h>
#include <data/datetimedecorator.h>
#include <data/stringdecorator.h>
#include <data/entity.h>

namespace br {
namespace models {


class BRAINRINGLIBSHARED_EXPORT Future : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(br::data::DateTimeDecorator* ui_startAt MEMBER startAt CONSTANT)
    Q_PROPERTY(br::data::StringDecorator* ui_notes MEMBER notes CONSTANT)
public:
    explicit Future(QObject* parent = nullptr);
    Future(QObject *parent, const QJsonObject& json);

    data::DateTimeDecorator* startAt{nullptr};
    data::StringDecorator* notes{nullptr};
};

}
}

#endif // FUTURE_H

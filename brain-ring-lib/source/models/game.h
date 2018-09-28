#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include "brain-ring-lib_global.h"
#include <data/stringdecorator.h>
#include <data/entity.h>
#include <data/entity-collection.h>


namespace br {
namespace models {

class BRAINRINGLIBSHARED_EXPORT Game : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(br::data::StringDecorator* ui_number MEMBER number CONSTANT)
    Q_PROPERTY(br::data::StringDecorator* ui_text MEMBER text CONSTANT)

public:
    explicit Game(QObject* parent = nullptr);
    Game(QObject *parent, const QJsonObject& json);

    data::StringDecorator* number{nullptr};
    data::StringDecorator* text{nullptr};

signals:

};

}
}

#endif // GAME_H

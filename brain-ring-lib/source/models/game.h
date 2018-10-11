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
    Q_PROPERTY(br::data::StringDecorator* ui_number READ number CONSTANT)
    Q_PROPERTY(br::data::StringDecorator* ui_text READ text CONSTANT)

public:
    explicit Game(QObject* parent = nullptr);
    Game(QObject *parent, const QJsonObject& json);
    ~Game();

    data::StringDecorator* number();
    data::StringDecorator* text();
    void clear();

signals:

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}

#endif // GAME_H

#ifndef PLAYER_H
#define PLAYER_H

#include <QObject>

#include "brain-ring-lib_global.h"
#include <data/entity.h>
#include <data/intdecorator.h>

namespace br {
namespace gameplay {

class BRAINRINGLIBSHARED_EXPORT Player : public data::Entity
{

    Q_OBJECT
    Q_PROPERTY(br::data::IntDecorator* ui_number READ number CONSTANT)
    Q_PROPERTY(br::data::StringDecorator* ui_points READ points CONSTANT)
public:
    explicit Player(QObject* parent = nullptr);
    Player(QObject* parent, const QJsonObject& json);
    ~Player();

    data::IntDecorator* number();
    data::StringDecorator* points();
    void clear();

signals:

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;


};

}
}
#endif // PLAYER_H

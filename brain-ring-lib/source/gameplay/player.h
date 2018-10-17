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
    Q_PROPERTY(br::data::StringDecorator* ui_number MEMBER number CONSTANT)
    Q_PROPERTY(br::data::IntDecorator* ui_points MEMBER points CONSTANT)
    Q_PROPERTY(br::data::StringDecorator* ui_isConnected MEMBER isConnected CONSTANT)
public:
    explicit Player(QObject* parent = nullptr);
    Player(QObject* parent, const QJsonObject& json);

    data::StringDecorator* number{nullptr};
    data::IntDecorator* points{nullptr};
    data::StringDecorator* isConnected{nullptr};
//    void clear();

};

}
}
#endif // PLAYER_H

#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QtQml/QQmlListProperty>

#include "brain-ring-lib_global.h"
#include <data/stringdecorator.h>
#include <data/entity.h>
#include <data/entity-collection.h>
#include <models/info.h>
#include <models/future.h>
#include <models/question.h>


namespace br {
namespace models {

class BRAINRINGLIBSHARED_EXPORT Game : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(br::data::StringDecorator* ui_reference MEMBER reference CONSTANT)
    Q_PROPERTY(br::data::StringDecorator* ui_name MEMBER name CONSTANT)
    Q_PROPERTY(br::models::Info* ui_supplyInfo MEMBER supplyInfo CONSTANT)
    Q_PROPERTY(QQmlListProperty<Future> ui_futures READ ui_futures NOTIFY futuresChanged)
    Q_PROPERTY(QQmlListProperty<Question> ui_questions READ ui_questions NOTIFY questionsChanged)

public:
    explicit Game(QObject* parent = nullptr);
    Game(QObject *parent, const QJsonObject& json);

    data::StringDecorator* reference{nullptr};
    data::StringDecorator* name{nullptr};
    Info* supplyInfo{nullptr};

    data::EntityCollection<Future>* futures{nullptr};
    data::EntityCollection<Question>* questions{nullptr};

    QQmlListProperty<br::models::Future> ui_futures();
    QQmlListProperty<br::models::Question> ui_questions();

signals:
    void futuresChanged();
    void questionsChanged();

};

}
}

#endif // GAME_H

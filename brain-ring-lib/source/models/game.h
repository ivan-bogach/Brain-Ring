#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QJsonObject>
#include<QtQml/QQmlListProperty>

#include "brain-ring-lib_global.h"
#include <data/stringdecorator.h>
#include <data/entity.h>
#include <data/entity-collection.h>
#include <models/question.h>

namespace br {
namespace models {

class BRAINRINGLIBSHARED_EXPORT Game : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(br::data::StringDecorator* ui_name MEMBER name CONSTANT)
    Q_PROPERTY(QQmlListProperty<Question> ui_questionsChanged READ ui_questions NOTIFY questionsChanged)

public:
    explicit Game(QObject* parent = nullptr);
    Game(QObject *parent, const QJsonObject& json);

    data::StringDecorator* name{nullptr};

    data::EntityCollection<Question>* questions{nullptr};

    QQmlListProperty<br::models::Question> ui_questions();

signals:
    void questionsChanged();
};

}
}

#endif // CLIENT_H

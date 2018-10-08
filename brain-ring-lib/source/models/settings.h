#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>

#include "brain-ring-lib_global.h"
#include <data/entity.h>
#include <data/stringdecorator.h>
#include <data/intdecorator.h>


namespace br {
namespace models {

class BRAINRINGLIBSHARED_EXPORT Settings : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(br::data::StringDecorator* ui_quantity MEMBER quantity CONSTANT)
    Q_PROPERTY(br::data::IntDecorator* ui_askQuestions MEMBER askQuestions CONSTANT)
public:
    explicit Settings(QObject* parent = nullptr);
    Settings(QObject* parent, const QJsonObject& json);

    void clear();
    data::StringDecorator* quantity{nullptr};
    data::IntDecorator* askQuestions{nullptr};
};

}}

#endif // SETTINGS_H

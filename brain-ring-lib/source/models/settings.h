#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QScopedPointer>

#include "brain-ring-lib_global.h"
#include <data/entity.h>
#include <data/stringdecorator.h>
#include <data/intdecorator.h>
#include <controllers/database-controller.h>


namespace br {
namespace models {

class BRAINRINGLIBSHARED_EXPORT Settings : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(br::data::IntDecorator* ui_quantity READ quantity CONSTANT)
    Q_PROPERTY(br::data::IntDecorator* ui_askQuestions READ askQuestions CONSTANT)
public:
    explicit Settings(QObject* parent = nullptr, controllers::IDatabaseController* databaseController = nullptr);
    ~Settings();

    void clear();

    data::IntDecorator* quantity();
    data::IntDecorator* askQuestions();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

};

}}

#endif // SETTINGS_H

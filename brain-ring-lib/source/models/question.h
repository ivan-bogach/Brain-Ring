#ifndef QUESTION_H
#define QUESTION_H

#include <QObject>

#include <brain-ring-lib_global.h>
#include <data/stringdecorator.h>
#include <data/intdecorator.h>
#include <data/entity.h>


namespace br {
namespace models {

class BRAINRINGLIBSHARED_EXPORT Question : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(br::data::StringDecorator* ui_text MEMBER text CONSTANT)
    Q_PROPERTY(br::data::IntDecorator* ui_number MEMBER number CONSTANT)
public:
    explicit Question(QObject* parent = nullptr);
    Question(QObject* parent, const QJsonObject& json);

    data::StringDecorator* text{nullptr};
    data::IntDecorator* number{nullptr};
};

}
}
#endif // QUESTION_H

#ifndef QUESTION_H
#define QUESTION_H

#include <QObject>
#include <brain-ring-lib_global.h>
#include <data/enumeratordecorator.h>
#include <data/stringdecorator.h>
#include <data/entity.h>

namespace br {
namespace models {


class BRAINRINGLIBSHARED_EXPORT Question : public data::Entity
{
    Q_OBJECT
    Q_PROPERTY(br::data::EnumeratorDecorator* ui_questionType MEMBER questionType CONSTANT)
    Q_PROPERTY(br::data::StringDecorator* ui_question MEMBER question CONSTANT)

public:
    enum eQuestionType{
//allows to accommodate an initial unset value.
        Unknown = 0,

        First,
        Second
    };

public:
    explicit Question(QObject* parent = nullptr);
    Question(QObject *parent, const QJsonObject& json);


    data::EnumeratorDecorator* questionType{nullptr};
    data::StringDecorator* question{nullptr};

//allows to map each of the enumerated types to a descriptivestring
    static std::map<int, QString> questionTypeMapper;
};

}
}

#endif // QUESTION_H

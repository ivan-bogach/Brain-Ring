#include "question.h"

using namespace br::data;

namespace br {
namespace models {

std::map<int, QString>Question::questionTypeMapper = std::map<int, QString>{
    {Question::eQuestionType::Unknown, ""}
    ,{Question::eQuestionType::First, "First"}
    ,{Question::eQuestionType::Second, "Second"}
};

Question::Question(QObject* parent)
    : Entity(parent, "question")
{
//    data::EnumeratorDecorator* questionType{nullptr};
//    data::StringDecorator* question{nullptr};
    questionType = static_cast<EnumeratorDecorator*>(addDataItem(new EnumeratorDecorator(this, "questionType", "Question Type", 0, Question::questionTypeMapper)));
    question = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "question", "Вопрос")));
}

Question::Question(QObject *parent, const QJsonObject &json)
    :Question(parent)
{
    update(json);
}

}
}

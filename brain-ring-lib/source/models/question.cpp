#include "question.h"

using namespace br::data;

namespace br {
namespace models {


Question::Question(QObject* parent)
: Entity(parent, "question")
{
    text = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "question", "ВопросЪ")));
    number = static_cast<IntDecorator*>(addDataItem(new IntDecorator(this, "number", 0)));
}

Question::Question(QObject *parent, const QJsonObject& json)
    : Question(parent)
{
    update(json);
}

}
}

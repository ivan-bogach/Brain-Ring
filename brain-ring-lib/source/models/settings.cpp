#include "settings.h"

using namespace br::controllers;
using namespace br::data;

namespace br {
namespace models {

class Settings::Implementation
{
public:
    Implementation(Settings* _settings, IDatabaseController* _databaseController)
        : settings(_settings)
        , databaseController(_databaseController)
    {}
    Settings* settings{nullptr};
    IDatabaseController* databaseController{nullptr};
    IntDecorator* quantity{nullptr};
    IntDecorator* askQuestion{nullptr};
    StringDecorator* bgColor{nullptr};
    StringDecorator* txtColor{nullptr};
};


Settings::Settings(QObject* parent, IDatabaseController* databaseController)
    : Entity(parent, "settings")
{
    implementation.reset(new Implementation(this, databaseController));
    implementation->quantity = static_cast<IntDecorator*>(addDataItem(new IntDecorator(this, "quantity", "Количество игроков")));
    implementation->askQuestion = static_cast<IntDecorator*>(addDataItem(new IntDecorator(this, "ask", "Ask")));
    implementation->bgColor = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "bgColor", "Color BG")));
    implementation->txtColor = static_cast<StringDecorator*>(addDataItem(new StringDecorator(this, "txtColor", " Color Text")));

    QJsonObject jsonObject = implementation->databaseController->readRow("settings", "1");
    implementation->askQuestion->setValue(jsonObject.value("ask").toInt());
    implementation->quantity->setValue(jsonObject.value("quantity").toInt());
    implementation->bgColor->setValue(jsonObject.value("bgColor").toString());
    implementation->txtColor->setValue(jsonObject.value("txtColor").toString());
}

Settings::~Settings(){}

IntDecorator* Settings::quantity()
{
    return implementation->quantity;
}

IntDecorator* Settings::askQuestions()
{
    return implementation->askQuestion;
}

StringDecorator* Settings::bgColor()
{
//    qDebug() << "bgColor: " << implementation->bgColor->value();
    return  implementation->bgColor;
}

StringDecorator* Settings::txtColor()
{
//    qDebug() << "txtColor: " << implementation->txtColor->value();
    return implementation->txtColor;
}

}}

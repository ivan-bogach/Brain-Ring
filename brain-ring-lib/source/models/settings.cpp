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
};


Settings::Settings(QObject* parent, IDatabaseController* databaseController)
    : Entity(parent, "settings")
{
    implementation.reset(new Implementation(this, databaseController));
    implementation->quantity = static_cast<IntDecorator*>(addDataItem(new IntDecorator(this, "quantity", "Количество игроков")));
    implementation->askQuestion = static_cast<IntDecorator*>(addDataItem(new IntDecorator(this, "ask", "Ask")));

    QJsonObject jsonObject = implementation->databaseController->readRow("settings", "1");
    implementation->askQuestion->setValue(jsonObject.value("ask").toInt());
    implementation->quantity->setValue(jsonObject.value("quantity").toInt());
}

Settings::~Settings(){}

IntDecorator* Settings::quantity()
{
//    qDebug() << "Settings::quantity:" << QString::number(implementation->quantity->value());
    return implementation->quantity;
}

IntDecorator* Settings::askQuestions()
{
    return implementation->askQuestion;
}

//Settings::Settings(QObject* parent, IDatabaseController* databaseController, const QJsonObject& json)
//    :Settings(parent)
//{
//    update(json);
//}



}}

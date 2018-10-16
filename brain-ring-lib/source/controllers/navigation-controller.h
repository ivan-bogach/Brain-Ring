#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H

#include <QObject>

#include <brain-ring-lib_global.h>
#include <models/game.h>
#include <data/intdecorator.h>

namespace br {
namespace controllers {

class BRAINRINGLIBSHARED_EXPORT NavigationController : public QObject
{
    Q_OBJECT
public:
    explicit NavigationController(QObject* parent = nullptr) : QObject(parent){}

signals:
//    void goGameView(br::models::Game* game);
    void goDashboardView();
    void goGameView();
    void goCreateGameView();
    void goSettingsView();
    void goGameQuestionView(br::models::Game* game);
    void goEmptyQuestionsListView();
    void goGameAnswerView(br::data::IntDecorator* number);
//    void goEditGameView(br::models::Game* game);
//    void goFindGameView();
};

}
}

#endif // NAVIGATIONCONTROLLER_H

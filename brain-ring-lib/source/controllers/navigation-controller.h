#ifndef NAVIGATIONCONTROLLER_H
#define NAVIGATIONCONTROLLER_H

#include <QObject>

#include <brain-ring-lib_global.h>
#include <models/game.h>

namespace br {
namespace controllers {

class BRAINRINGLIBSHARED_EXPORT NavigationController : public QObject
{
    Q_OBJECT

public:
    explicit NavigationController(QObject* _parent = nullptr)
        : QObject(_parent)
    {}

signals:
    void goCreateGameView();
    void goDashboardView();
    void goSettingsView();
//    void goStartGameView(br::models::Game);
    void goStartGameView();
};

}
}

#endif // NAVIGATIONCONTROLLER_H


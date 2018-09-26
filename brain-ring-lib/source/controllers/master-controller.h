#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QScopedPointer>
#include <QString>

#include <brain-ring-lib_global.h>
#include <controllers/navigation-controller.h>
#include <controllers/command-controller.h>
#include <models/game.h>



namespace br {
namespace controllers {


class BRAINRINGLIBSHARED_EXPORT MasterController : public QObject
{
    Q_OBJECT

// creating	a new	property of the	QString	type to be able to access this member from QML
// refer to the property	as ui_welcomeMessage and get (or set) the	value in the MEMBER welcomeMessage
    Q_PROPERTY(QString ui_welcomeMessage READ welcomeMessage CONSTANT)
    Q_PROPERTY(br::controllers::NavigationController* ui_navigationController READ navigationController CONSTANT)
    Q_PROPERTY(br::controllers::Commandcontroller* ui_commandController READ commandController CONSTANT)
    Q_PROPERTY(br::models::Game* ui_newGame READ newGame CONSTANT)

public:
    explicit MasterController(QObject *parent = nullptr);
    ~MasterController();

    NavigationController* navigationController();
    Commandcontroller* commandController();
    models::Game* newGame();

    const QString& welcomeMessage() const;

signals:

public slots:

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}

#endif // MASTERCONTROLLER_H

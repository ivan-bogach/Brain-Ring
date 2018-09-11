#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H

#include <QObject>
#include <QString>

#include <brain-ring-lib_global.h>

namespace br {
namespace controllers {


class BRAINRINGLIBSHARED_EXPORT MasterController : public QObject
{
    Q_OBJECT

// creating	a new	property of the	QString	type to be able to access this member from QML
// refer to the property	as ui_welcomeMessage and get (or set) the	value in the MEMBER welcomeMessage
    Q_PROPERTY(QString ui_welcomeMessage MEMBER welcomeMessage CONSTANT)
public:
    explicit MasterController(QObject *parent = nullptr);

    QString welcomeMessage = "This is from Master COntroller header.";

signals:

public slots:
};

}
}

#endif // MASTERCONTROLLER_H

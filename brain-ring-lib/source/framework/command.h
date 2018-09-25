#ifndef COMMAND_H
#define COMMAND_H

#include <functional>

#include <QObject>
#include <QScopedPointer>
#include <QString>


#include <brain-ring-lib_global.h>


namespace br {
namespace framework {

class BRAINRINGLIBSHARED_EXPORT Command : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString ui_icon READ icon CONSTANT)
    Q_PROPERTY(QString ui_description READ description CONSTANT)
    Q_PROPERTY(bool ui_canExecute READ canExecute NOTIFY canExecuteChanged)
public:
    explicit Command(QObject *parent = nullptr, const QString& icon = "", const QString& description = "", std::function<bool()> canExecute = [](){ return true;});
    ~Command();

    const QString& icon() const;
    const QString& description() const;
    bool canExecute() const;

signals:
    void canExecuteChanged();
    void executed();

public slots:

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}

#endif // COMMAND_H

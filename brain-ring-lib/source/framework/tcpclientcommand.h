#ifndef TCPCLIENTCOMMAND_H
#define TCPCLIENTCOMMAND_H

#include <QObject>

#include <brain-ring-lib_global.h>

namespace br {
namespace framework {


class BRAINRINGLIBSHARED_EXPORT TCPClientCommand : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString ui_number READ number CONSTANT)
    Q_PROPERTY(QString ui_icon READ icon CONSTANT)
public:
    explicit TCPClientCommand(QObject* parent = nullptr, const QString& number = "", const QString& icon = "");
    ~TCPClientCommand();

    const QString& number() const;
    const QString& icon() const;
signals:
    void executed();

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;

};



}
}
#endif // TCPCLIENTCOMMAND_H

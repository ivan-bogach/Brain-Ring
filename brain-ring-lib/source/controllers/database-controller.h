#ifndef DATABASECONTROLLER_H
#define DATABASECONTROLLER_H

#include<QObject>
#include <QScopedPointer>

#include <controllers/i-database-controller.h>

#include <brain-ring-lib_global.h>

namespace br {
namespace controllers {

class BRAINRINGLIBSHARED_EXPORT DatabaseController : public IDatabaseController
{
    Q_OBJECT
public:
    explicit DatabaseController(QObject* parent = nullptr);
    ~DatabaseController();

    bool createRow(const QString& tableName, const QString& id, const QJsonObject& jsonObject) const override;
//    bool deleteRow(const QString& tableName, const QString& id) const override;
//    QJsonArray find(const QString& tableName, const QString& searchText) const override;
    QJsonArray findAll(const QString& tableName) const override;
//    QJsonObject readRow(const QString& tableName, const QString& id) const override;
    bool updateRow(const QString& tableName, const QString& id, const QJsonObject& jsonObject) const override;

private:
    class Implementation;
    QScopedPointer<Implementation> implementation;
};

}
}

#endif // DATABASECONTROLLER_H

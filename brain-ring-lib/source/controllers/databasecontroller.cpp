#include "databasecontroller.h"

#include <QDebug>
#include <QJsonDocument>
#include <QSqlDatabase>
#include <QSqlQuery>

namespace br {
namespace controllers {

class DatabaseController::Implementation
{
public:
    Implementation(DatabaseController* _databaseController)
        : databaseController(_databaseController)
    {
        if (initialise()) {
            qDebug() << "Database created using Sqlite version: " + sqliteVersion();
            if (createTables()) {
                qDebug() << "Database tables created";
            } else {
                qDebug() << "ERROR: Unable to create database tables";
            }
        } else {
            qDebug() << "ERROR: Unable to open database";
        }
    }

    DatabaseController* databaseController{nullptr};
    QSqlDatabase database;

private:

    bool initialise()
    {
//QSqlDatabase QSqlDatabase::addDatabase(const QString &type, const QString &connectionName = QLatin1String(defaultConnection)) -
//Adds a database to the list of database connections using the driver type and the connection name connectionName
        database = QSqlDatabase::addDatabase("QSQLITE", "brain-ring");

//void QSqlDatabase::setDatabaseName(const QString &name) - Sets the connection's database name to name
        database.setDatabaseName("brain-ring.sqlite");

//bool QSqlDatabase::open() - Opens the database connection using the current connection values
        return database.open();
    }

    bool createTables()
    {
        return createJsonTable("game");
    }

    bool createJsonTable(const QString& tableName) const
    {
//The QSqlQuery class provides a means of executing and manipulating SQL statements
//QSqlQuery::QSqlQuery(QSqlDatabase db) Constructs a QSqlQuery object using the database db
        QSqlQuery query(database);

        QString sqlStatement = "CREATE TABLE IF NOT EXISTS " + tableName + " (id text primary key, json text not null)";

//bool QSqlQuery::prepare(const QString &query) - Prepares the SQL query query for execution
        if(!query.prepare(sqlStatement)) return false;

//bool QSqlQuery::exec() - Executes a previously prepared SQL query
        return query.exec();
    }

    QString sqliteVersion() const
    {
        QSqlQuery query(database);
        query.exec("SELECT sqlite_version()");

//bool QSqlQuery::next() - Retrieves the next record in the result, if available, and positions the query on the retrieved record
        if(query.next()) return query.value(0).toString();

        return QString::number(-1);
    }
};
}

namespace controllers {


DatabaseController::DatabaseController(QObject* parent)
    :IDatabaseController(parent)
{
    implementation.reset(new Implementation(this));
}

DatabaseController::~DatabaseController(){}

bool DatabaseController::createRow(const QString& tableName, const QString& id, const QJsonObject& jsonObject) const
{
    qDebug() << "I AM HERE";
    if(tableName.isEmpty()) return false;
    if(id.isEmpty()) return false;
    if(jsonObject.isEmpty()) return false;

    QSqlQuery query(implementation->database);
    QString sqlStatement = "INSERT OR REPLACE INTO " + tableName + " (id, json) VALUES (:id, :json)";

    if (!query.prepare(sqlStatement)) return false;

//void QSqlQuery::bindValue(const QString &placeholder, const QVariant &val, QSql::ParamType paramType = QSql::In)
//Set the placeholder placeholder to be bound to value val in the prepared statement
    query.bindValue(":id", QVariant(id));

//QJsonDocument::QJsonDocument(const QJsonObject &object) - Creates a QJsonDocument from object.
//QByteArray QJsonDocument::toJson() const - Converts the QJsonDocument to a UTF-8 encoded JSON document.
    query.bindValue(":json", QVariant(QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)));

    if(!query.exec()) return false;

//int QSqlResult::numRowsAffected() - Returns the number of rows affected by the last query executed, or -1
    return query.numRowsAffected() > 0;
}

bool DatabaseController::deleteRow(const QString& tableName, const QString& id) const
{
    if(tableName.isEmpty()) return false;
    if(id.isEmpty()) return false;

    QSqlQuery query(implementation->database);

    QString sqlStatement = "DELETE FROM " + tableName + " WHERE id=:id";

    if(!query.prepare(sqlStatement)) return false;

    query.bindValue(":id", QVariant(id));

    if(!query.exec()) return false;

    return query.numRowsAffected() > 0;
}

QJsonObject DatabaseController::readRow(const QString& tableName, const QString& id) const
{
    if(tableName.isEmpty()) return {};
    if(id.isEmpty()) return {};

    QSqlQuery query(implementation->database);

    QString sqlStatement = "SELECT json FROM " + tableName + " WHERE id=:id";

    if(!query.prepare(sqlStatement)) return {};

    query.bindValue(":id", QVariant(id));

    if(!query.exec()) return {};

    if(!query.first()) return {};

    auto json = query.value(0).toByteArray();
    auto jsonDocument = QJsonDocument::fromJson(json);

    if(!jsonDocument.isObject()) return {};
    return jsonDocument.object();

}

bool DatabaseController::updateRow(const QString& tableName, const QString& id, const QJsonObject& jsonObject) const
{
    if(tableName.isEmpty()) return false;
    if(id.isEmpty()) return false;
    if(jsonObject.isEmpty()) return false;

    QSqlQuery query(implementation->database);

    QString sqlStatement = "UPDATE " + tableName + " SET json=:json WHERE id=:id";

    if(!query.prepare(sqlStatement)) return false;

    query.bindValue(":id", QVariant(id));
    query.bindValue(":json", QVariant(QJsonDocument(jsonObject).toJson(QJsonDocument::Compact)));

    if(!query.exec()) return false;

    return query.numRowsAffected() > 0;
}

QJsonArray DatabaseController::find(const QString& tableName, const QString& searchText) const
{
    if(tableName.isEmpty()) return {};
    if(searchText.isEmpty()) return {};
    QSqlQuery query(implementation->database);

    QString sqlStatement = "SELECT json FROM " + tableName + " WHERE lower(json) like :searchText";

    if(!query.prepare(sqlStatement)) return {};

    query.bindValue(":searchText", QVariant("%" + searchText.toLower() + "%"));

    if(!query.exec()) return {};

    QJsonArray returnValue;

    while (query.next())
    {
        auto json = query.value(0).toByteArray();
        auto jsonDocument = QJsonDocument::fromJson(json);
        if(jsonDocument.isObject())
        {
            returnValue.append(jsonDocument.object());
        }
    }
    return returnValue;
}

}
}

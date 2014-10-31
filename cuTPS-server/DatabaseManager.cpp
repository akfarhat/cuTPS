#include "DatabaseManager.h"

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
}

DatabaseManager::~DatabaseManager() {

}

bool DatabaseManager::openDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("cutps.db");
    return db.open();
}

bool DatabaseManager::closeDB()
{
    db.close();
}

QSqlError DatabaseManager::getLastError()
{
    return db.lastError();
}

bool DatabaseManager::runQuery(const QString &queryString, QSqlQuery* returnQuery)
{
    QSqlQuery query(queryString);
    bool result = query.exec();

    *returnQuery = query;
    return result;
}


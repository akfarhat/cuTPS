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

QSqlQuery DatabaseManager::runQuery(const QString &queryString)
{
    QSqlQuery query(queryString);
    query.exec();
    return query;
}


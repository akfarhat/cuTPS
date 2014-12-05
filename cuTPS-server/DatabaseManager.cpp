#include "DatabaseManager.h"
#include "ServerPrefs.h"
#include <iostream>

DatabaseManager::DatabaseManager(QObject *parent) :
    QObject(parent)
{
}

DatabaseManager::~DatabaseManager() {

}

bool DatabaseManager::openDB()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = ServerPrefs::GetDbPath();
    db.setDatabaseName(dbPath);

    bool result = db.open();
    if (!result)
    {
        // TODO: Throw an exception
        qDebug() << "cannot find cutps.db in " << dbPath
                  << "make sure the software was installed properly";
    } else {
        qDebug() << "using database file: " << dbPath;
    }

    return result;
}

void DatabaseManager::closeDB()
{
    db.close();
}

QSqlError DatabaseManager::getLastError()
{
    return db.lastError();
}

bool DatabaseManager::runQuery(const QString &queryString, QSqlQuery* returnQuery)
{
    QSqlQuery query;
    bool result = query.exec(queryString);

    *returnQuery = query;
    return result;
}

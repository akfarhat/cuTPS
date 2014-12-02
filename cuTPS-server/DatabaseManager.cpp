#include "DatabaseManager.h"
#include "TPSServerPrefs.h"
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
    QString dbPath = TPSServerPrefs::GetDbPath();
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

bool DatabaseManager::runQuery(QSqlQuery& returnQuery)
{
    bool result = query.exec();

    return result;
}


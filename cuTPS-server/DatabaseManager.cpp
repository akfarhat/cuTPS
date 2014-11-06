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

    //QString dbPath = QCoreApplication::applicationDirPath() + "/cutps.db";

    QString dbPath = "/home/student/Comp3004/cuTPS/cutps.db";
    qDebug() << "dbPath: '" << dbPath << "'";

    db.setDatabaseName(dbPath);
    return db.open();
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


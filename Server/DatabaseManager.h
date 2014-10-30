#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QtSql>

class DatabaseManager : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseManager(QObject *parent = 0);
    ~DatabaseManager();

public:
    bool openDB();
    bool closeDB();
    QSqlError getLastError();
    QSqlQuery runQuery(const QString& queryString);



private:
    QSqlDatabase db;


};

#endif // DATABASEMANAGER_H

// Class: DatabaseManager
// Type: Control
// Description:
//     Responsible for connecting to, and executing queries on the database

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
    // Open a connection to the database
    bool openDB();

    // Close the connection to the database
    // TODO: Document possible exceptions thrown here, like InvalidConnection
    void closeDB();

    // returns the last error encountered by the database wrapper
    QSqlError getLastError();

    // Runs the query provided
    // Params:
    //     queryString (QString&): the correctly formatted SQL query to run
    //     (QSqlQuery*) : The compiled and executed query objected being returned
    // Returns:
    //     (bool): true if the query was successful, false otherwise.
    bool runQuery(QSqlQuery&);

private:
    QSqlDatabase db;


};

#endif // DATABASEMANAGER_H

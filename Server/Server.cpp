#include "Server.h"

Server::Server(QObject *parent) :
    QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("cutps.db");
    if (! db.open()) {
        cout << "Error opening database connection to cutps.db: "
             << db.lastError();
    }

}

ServerResponse Server::authenticateUser(int sessionID, UserCredentials creds)
{

}

Server::~Server() {}

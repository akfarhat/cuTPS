#include "Server.h"

#include <QSqlError>
#include <iostream>

Server::Server(QObject *parent) :
    QObject(parent)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("cutps.db");
    if (! db.open()) {
        std::cout << "Error opening database connection to cutps.db: "
                  << db.lastError().text().toUtf8().constData();
    }

}

ServerResponse Server::authenticateUser(int sessionID, UserCredentials creds)
{

}

Server::~Server() {}

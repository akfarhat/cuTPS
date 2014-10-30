#include "Server.h"

#include <QSqlError>
#include <iostream>

Server::Server(QObject *parent) :
    QObject(parent)
{
    dbManager = new DatabaseManager();

    if (!dbManager->openDB()) {
        throw dbManager->getLastError();
    }

}

Server::~Server()
{
    dbManager->closeDB();
}

QUuid Server::generateSessionID(QString* errorMessage)
{
    if (openSessions.size() >= MAX_SESSIONS) {
        *errorMessage = "Exceeded maximum number of open sessions";
        return 0;
    }

    QUuid sessionID = QUuid.createUuid();
    int i = 1;

    // attempt to generate a UUID at most 10 times
    while(openSessions.contains(sessionID) && i < 10) {
        sessionID = QUuid.createUuid();
        i++;
    }

    if (i < 10) {
        openSessions.append(sessionID);
        return sessionID;
    }
    else {
        return 0;
    }
}

ServerResponse Server::createSession()
{
    ServerResponse response;
    response.sessionID = generateSessionID(response.message);

    if (response.sessionID) {
        response.code = ResponseCode::Success;
    }
    else {
        response.code = ResponseCode::Fail;
    }
}

ServerResponse Server::authenticateUser(QUuid sessionID, UserCredentials creds)
{
    QSqlQuery query = dbManager->runQuery("select * from User where username = " + creds.username + " and password = " + creds.password + ";");

    ServerResponse response;
    response.sessionID = sessionID;

    if(query.first()) {
        response.code = ResponseCode::Success;
    }
    else {
        response.code = ResponseCode::Fail;
    }

    return response;
}


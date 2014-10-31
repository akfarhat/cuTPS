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

QUuid Server::generateSessionID(QString& errorMessage)
{
    if (openSessions.size() >= MAX_SESSIONS) {
        errorMessage = "Exceeded maximum number of open sessions";
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
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;
    bool result = dbManager->runQuery("select * from User where username = " +
                                      creds.username + " and password = " +
                                      creds.password + ";", &query);

    if (result) {
        if (query.first()) {
            response.code = ResponseCode::Success;
            response.message = "";
        }
        else {
            response.code = ResponseCode::Fail;
            response.message = "Invalid credentials, user not found.";
        }
    }
    else {
        response.code = ResponseCode::Fail;
        response.message = query.lastError().text();
    }

    return response;
}

ServerResponse Server::addCourse(QUuid sessionID, Course course)
{
    ServerResponse response;
    response.sessionID = sessionID;

    SqlQuery query;
    bool result = dbManager->runQuery("insert into Course (code, name) " +
                                      " values (" +
                                      course.getCourseCode() + ", " +
                                      course.getCourseName() + ")" +
                                      ";", &query);

    if (result) {
        response.code = ResponseCode::Success;
        response.message = "";
    }
    else {
        response.code = ResponseCode::Fail;
        response.message = query.lastError().text();
        return response;
    }

    foreach (textbook, course.getRequiredTexts()) {
        result = dbManager->runQuery("insert into Course_Textbook (course_id, textbook_id) " +
                                     "values (" + course.getID() + ", " + textbook.getID() +
                                     ");", &query);

        if (result) {
            response.code = ResponseCode::Success;
            response.message = "";
        }
        else {
            response.code = ResponseCode::Fail;
            response.message = query.lastError().text();
            return response;
        }
    }

    return response;
}

ServerResponse Server::addTextbook(QUuid sessionID, Textbook textbook)
{
    ServerResponse response;
    response.sessionID = sessionID;

    SqlQuery query;
    bool result = dbManager->runQuery("insert into Textbook (name, available) " +
                                      " values (" +
                                      textbook.getName() + ", " +
                                      textbook.getAvailable() + ")" +
                                      ";", &query);

    if (result) {
        response.code = ResponseCode::Success;
        response.message = "";
    }
    else {
        response.code = ResponseCode::Fail;
        response.message = query.lastError().text();
        return response;
    }

    return response;
}

ServerResponse Server::addChapter(QUuid sessionID, Chapter chapter)
{
    ServerResponse response;
    response.sessionID = sessionID;

    SqlQuery query;
    bool result = dbManager->runQuery("insert into Chapter (textbook_id, name, available) " +
                                      " values (" +
                                      chapter.getTextbook().getID() + ", " +
                                      chapter.getName() + ", " +
                                      chapter.getAvailable() + ")" +
                                      ";", &query);

    if (result) {
        response.code = ResponseCode::Success;
        response.message = "";
    }
    else {
        response.code = ResponseCode::Fail;
        response.message = query.lastError().text();
        return response;
    }

    return response;
}

ServerResponse Server::addSection(QUuid sessionID, Section section)
{
    ServerResponse response;
    response.sessionID = sessionID;

    SqlQuery query;
    bool result = dbManager->runQuery("insert into Section (chapter_id, name, available) " +
                                      " values (" +
                                      section.getChapter().getID() + ", " +
                                      section.getName() + ", " +
                                      section.getAvailable() + ")" +
                                      ";", &query);

    if (result) {
        response.code = ResponseCode::Success;
        response.message = "";
    }
    else {
        response.code = ResponseCode::Fail;
        response.message = query.lastError().text();
        return response;
    }

    return response;
}


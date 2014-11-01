#include "Server.h"

#include <QSqlError>
#include <QRegExp>

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

bool Server::generateSessionID(QUuid& sessionID, QString& errorMessage)
{
    if (openSessions.size() >= MAX_SESSIONS) {
        errorMessage = "Exceeded maximum number of open sessions";
        return false;
    }

    QUuid id = QUuid::createUuid();
    int i = 1;

    // attempt to generate a UUID at most 10 times
    while(openSessions.contains(id) && i < 10) {
        id = QUuid::createUuid();
        i++;
    }

    if (i < 10) {
        openSessions.append(id);
        sessionID = id;
        return true;
    }
    else {
        return false;
    }
}

ServerResponse Server::createSession()
{
    ServerResponse response;
    bool result = generateSessionID(response.sessionID, response.message);

    if (result) {
        response.code = Success;
    }
    else {
        response.code = Fail;
    }

    return response;
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
            response.code = Success;
            response.message = "";
        }
        else {
            response.code = Fail;
            response.message = "Invalid credentials, user not found.";
        }
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();
    }

    return response;
}

ServerResponse Server::addCourse(QUuid sessionID, Course course)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;
    bool result = dbManager->runQuery("insert into Course (code, name) values (" +
                                      course.getCourseCode() + ", " +
                                      course.getCourseName() + ")" +
                                      ";", &query);

    if (result) {
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();
        return response;
    }

    foreach (Textbook* textbook, course.getRequiredTexts()) {
        QString queryString = "insert into Course_Textbook (course_id, textbook_id) values (";
        queryString += course.getId();
        queryString += ", ";
        queryString += textbook->getId();
        queryString += ");";

        result = dbManager->runQuery(queryString, &query);

        if (result) {
            response.code = Success;
            response.message = "";
        }
        else {
            response.code = Fail;
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

    QSqlQuery query;
    bool result = dbManager->runQuery("insert into SellableItem (available) values (" +
                                      textbook.getName() + ", " +
                                      textbook.getAvailability() + ")" +
                                      ";", &query);

    if (result) {
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();
        return response;
    }

    result = dbManager->runQuery("insert into Textbook (name, available) values (" +
                                 textbook.getName() + ", " +
                                 textbook.getAvailability() + ")" +
                                 ";", &query);

    if (result) {
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();
        return response;
    }

    return response;
}

ServerResponse Server::addChapter(QUuid sessionID, Chapter chapter)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;
    QString queryString = "insert into Chapter (textbook_id, name, available) values (";
    queryString += chapter.getParentTextbook()->getId();
    queryString += ", ";
    queryString += chapter.getName();
    queryString += ", ";
    queryString += chapter.getAvailability();
    queryString += ");";

    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();
        return response;
    }

    return response;
}

ServerResponse Server::addSection(QUuid sessionID, Section section)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;
    QString queryString = "insert into Section (chapter_id, name, available) values (";
    queryString += section.getParentChapter()->getId();
    queryString += ", ";
    queryString += section.getName();
    queryString += ", ";
    queryString += section.getAvailability();
    queryString += ");";

    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();
        return response;
    }

    return response;
}

bool Server::validateBillingInfo(BillingInfo *billingInfo)
{
    if (billingInfo == NULL)
        return false;

    // Could potentially call a validator API from the billing system
    return true;
}

bool Server::validateDeliveryInfo(DeliveryInfo *deliveryInfo)
{
    if (deliveryInfo == NULL)
        return false;

    // Validate the delivery email address
    QRegExp re( QString("[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,4}") );
    re.setCaseSensitivity(Qt::CaseInsensitive);

    return re.exactMatch(deliveryInfo->getEmailAddress());
}

bool Server::validateOrder(Order& order, QString *errorMessage)
{
    if (! validateBillingInfo(order.getBillingInfo())) {
        *errorMessage = QString("Invalid billing information");
        return false;
    }

    if (! validateDeliveryInfo(order.getDeliveryInfo())) {
        *errorMessage = QString("Invalid delivery information");
        return false;
    }

    if (! order.getOrder().size() > 0) {
        *errorMessage = QString("Order must have at least one item");
        return false;
    }

    return true;
}

ServerResponse Server::submitOrder(QUuid sessionID, Order order)
{
    ServerResponse response;
    response.sessionID = sessionID;

    bool result = validateOrder(order, &(response.message));

    if (result) {
        response.code = Success;
        // submit order to external system
    }
    else {
        response.code = Fail;
    }

    return response;
}


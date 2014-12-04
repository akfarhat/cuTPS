#include "Server.h"

#include <QSqlError>
#include <QDebug>
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

ServerResponse Server::closeSession(QUuid sessionID)
{
    ServerResponse response;

    int index = openSessions.indexOf(sessionID);

    if (index > -1) {
        openSessions.remove(index);
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = "Session not found";
    }

    return response;
}

// TODO: This is dumb. We should add a "type" attribute to
// the User table and get rid of this function, since the
// authenticateUser can select the attribute.
Role Server::getUserRole(QString &username)
{
    QSqlQuery query;
    bool result;

    result = dbManager->runQuery("SELECT * FROM Student s JOIN User u ON (u.id=s.user_id) "
                                 "WHERE u.username = \"" + username + "\";",
                                 &query);
    if (result)
        if (query.first())
            return Role::StudentUser;

    result = dbManager->runQuery("SELECT * FROM ContentManager cm JOIN User u ON (u.id=cm.user_id) "
                                 "WHERE u.username = \"" + username + "\";",
                                 &query);
    if (result)
        if (query.first())
            return Role::ContentManagerUser;

    result = dbManager->runQuery("SELECT * FROM Administrator a JOIN User u ON (u.id=a.user_id) "
                                 "WHERE u.username = \"" + username + "\";",
                                 &query);
    if (result)
        if (query.first())
            return Role::AdministratorUser;

    return Role::None;
}

ServerResponse Server::authenticateUser(QUuid sessionID, Role &userRole, UserCredentials creds)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;
    bool result = dbManager->runQuery("select * from User where username = \"" +
                                      creds.username + "\" and password = \"" +
                                      creds.password + "\";", &query);

    if (result) {
        if (query.first()) {
            response.code = Success;
            response.message = "";

            userRole = getUserRole(creds.username);
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

    QString queryString = "insert into Course (code, name) values (\"" +
                           course.getCourseCode() + "\", \"" +
                           course.getCourseName() + "\")" +
                           ";";

    qDebug() << "About to insert Course, query'"
             << queryString << "'";

    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();

        qDebug() << "Failed to insert course: " << response.message;
        return response;
    }

    qDebug() << "About to insert " //<< QString::number(course.getRequiredTexts()->size())
             << " Course_Textbooks";

    for (Textbook* textbook : *(course.getRequiredTexts())) {
        // TODO: this is we should form the query for all books and execute it once.
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

            qDebug() << "Failed to insert Course_Textbook: " << response.message;
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

    QString queryString = "insert into SellableItem (name, price_cents, available) values (\"" +
                           textbook.getName() + "\", " +
            QString::number(textbook.getPriceCents()) + ", " +
                           QString::number(textbook.getAvailability()) + ");";

    qDebug() << "Server::addTextbook running query: '" << queryString << "'";
    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();

        qDebug() << "Server::addTextbook Failed to insert into SellableItem: "
                 << response.message;
        return response;
    }

    queryString = "insert into Textbook (isbn) values (\"" +
                  textbook.getISBN() + "\");";

    result = dbManager->runQuery(queryString, &query);

    qDebug() << "Server::addTextbook running query: '" << queryString << "'";

    if (result) {
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();

        qDebug() << "Server::addTextbook Failed to insert into Textbook: "
                 << response.message;
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

ServerResponse Server::getRequiredTextbooks(QUuid sessionID,const QString& username, QVector<int>* textbookIDs)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;

    QString queryString = "";
    queryString += "select Course_Textbook.textbook_id from User ";
    queryString += "join User_Course on User.id = User_Course.user_id ";
    queryString += "join Course_Textbook on User_Course.course_id = Course_Textbook.course_id ";
    queryString += "where User.username = \"";
    queryString += username;
    queryString += "\";";

    qDebug() << "query string: '" << queryString << "'";
    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        qDebug() << "Query for required texts successful. Rows: " << query.size();

        while(query.next()) {
            textbookIDs->append(query.value(0).toInt());
        }

        // TODO : send textbookIDs to client

        response.code = Success;
        response.message = "";
    }
    else {
        qDebug() << "Query for required texts failed.";

        response.code = Fail;
        response.message = query.lastError().text();
    }

    return response;
}

ServerResponse Server::getTextbookDetails(QUuid sessionID, int textbookID, Textbook** textbook)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;

    qDebug() << "textBookId param in server API = " << textbookID;

    QString queryString = "";
    queryString += "select SellableItem.id, SellableItem.name, SellableItem.price_cents, SellableItem.available, Textbook.isbn from Textbook, SellableItem ";
    queryString += "where Textbook.item_id = ";
    queryString += QString::number(textbookID);
    queryString += ";";

    qDebug() << "getBookDetails query string: '" << queryString << "'";

    bool result = dbManager->runQuery(queryString, &query);

    qDebug() << "query result: " << result;

    // TODO : Handle case where attributes are null
    if (result) {
        while(query.next()) {
            // TODO: remove this debug log
            qDebug() << "Adding a textbook("
                     << query.value(0).toInt() << ", "
                     << query.value(1).toString() << ", "
                     << query.value(2).toInt() << ", "
                     << query.value(3).toBool() << ", "
                     << query.value(4).toString() << ")";

            *textbook = new Textbook(
                query.value(0).toInt(),
                query.value(1).toString(),
                query.value(2).toInt(),
                query.value(3).toBool(),
                query.value(4).toString()
            );
        }

        // TODO : send textbook object to client

        response.code = Success;
        response.message = "";
    }
    else {

        // Failed to query DB, provide empty book
        *textbook = new Textbook();

        response.code = Fail;
        response.message = query.lastError().text();
    }

    return response;
}

ServerResponse Server::getTextbookParts(QUuid sessionID, int textbookID, QVector<SellableItem*>* parts)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;

    QString queryString = "";
    queryString += "select Chapter.item_id, Chapter.chapter_num, SellableItem.name, SellableItem.price, SellableItem.available from Chapter ";
    queryString += "where Chapter.textbook_id = ";
    queryString += textbookID;
    queryString += ";";

    bool result = dbManager->runQuery(queryString, &query);

    QVector<Chapter*> chapters;

    if (result) {
        while(query.next()) {
            chapters.append(
                        new Chapter(
                            query.value(0).toInt(),
                            NULL,
                            query.value(1).toInt(),
                            query.value(2).toString(),
                            query.value(3).toInt(),
                            query.value(4).toBool()
                            ));
        }

    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();
        return response;
    }

    for (Chapter* chapter : chapters) {

        parts->append(chapter);

        queryString = "";
        queryString += "select Section.item_id, Section.section_num, SellableItem.name, SellableItem.price, SellableItem.available from Section ";
        queryString += "where Section.chapter_id = ";
        queryString += chapter->getId();
        queryString += ";";

        result = dbManager->runQuery(queryString, &query);

        if (result) {
            while(query.next()) {
                parts->append(
                            new Section(
                                query.value(0).toInt(),
                                NULL,
                                query.value(1).toInt(),
                                query.value(2).toString(),
                                query.value(3).toInt(),
                                query.value(4).toBool()
                                ));
            }

        }
        else {
            response.code = Fail;
            response.message = query.lastError().text();
            return response;
        }

    }

    response.code = Success;
    response.message = "";

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
    QRegExp re( QString("[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}") );
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

    if (! order.getOrder()->size() > 0) {
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


#include "Server.h"

#include <QSqlError>
#include <QDebug>
#include <QRegExp>

#include <iostream>

#include "SecurityUtils.h"

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
    SecurityUtils security;
    response.sessionID = sessionID;
    QSqlQuery query;

    // Get password hash from db
    QString queryString = "select password, role from User where username = \""
            + creds.username + "\";";

    bool result = dbManager->runQuery(queryString,
                                      &query);

    if (result) {
        if (query.first()) {
            QString hash = query.value(0).toString();
            bool success = security.validatePassword(creds.username,
                                                     creds.password,
                                                     hash);
            if (success) {
                response.code = Success;
                int uRole = query.value(1).toInt();

                switch (uRole) {
                case 0:
                    userRole = Role::AdministratorUser;
                    break;
                case 1:
                    userRole = Role::ContentManagerUser;
                    break;
                case 2:
                    userRole = Role::StudentUser;
                    break;
                }

            } else {
                response.code = Fail;
            }
        } else {
            response.code = Fail;
        }
    } else {
        response.message = query.lastError().text();

        qDebug() << "Failed to auth user: " << response.message;
        response.code = Fail;
    }

    return response;
}

ServerResponse Server::addCourse(QUuid sessionID, Course& course, qint32* newId)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;

    QString queryString = "insert into Course (code, name, term_section, term_year) values (\"" +
            course.getCourseCode() + "\", \"" +
            course.getCourseName() + "\", \"" +
            course.getTermSection().at(0) + "\", " +
            course.getTermYear() + ");";

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

    for (int textbookId : course.getRequiredTextIds()) {
        // TODO: this is we should form the query for all books and execute it once.
        QString queryString = "insert into Course_Textbook (course_id, textbook_id) values (";
        queryString += course.getId();
        queryString += ", ";
        queryString += textbookId;
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

ServerResponse Server::addTextbook(QUuid sessionID, Textbook& textbook, qint32* newId)
{
    // TODO: For every chapter in textbook (i.e. textbook.getChapterList()) -- add them all as well.
    //       Same goes for every section of every chapter (i.e. chapter.getSectionList())
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;

    QString queryString = "insert into SellableItem (name, price_cents, available) values (\"" +
                           textbook.getName() + "\", " +
            QString::number(textbook.getPriceCents()) + ", " +
                           QString::number(textbook.getAvailability()) + ");";

    qDebug() << "Server::addTextbook running query: '" << queryString << "'";
    bool result = dbManager->runQuery(queryString, &query);

    // if that doesn't work, use query "select seq from sqlite_sequence where name="table_name""
    qint32 lastInsertId = query.lastInsertId().toInt();

    if (result) {
        response.code = Success;
        response.message = "";
        *newId = lastInsertId;
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

    qint32 stub;
    for (Chapter* c : textbook.getChapterList())
    {
        addChapter(sessionID, *c, &stub);
    }

    return response;
}

ServerResponse Server::addChapter(QUuid sessionID, Chapter& chapter, qint32* newId)
{
    // TODO: Also add every section of the chapter -- i.e. chapter.getSectionList()
    ServerResponse response;
    response.sessionID = sessionID;
    QSqlQuery query;

    // TODO: ensure that getParentChapterId() belongs to getParentTextbookId().

    QString queryString = "insert into SellableItem (name, price_cents, available) values (";
    queryString += "\"" + chapter.getName() + "\", ";
    queryString += QString::number(chapter.getPriceCents()) + ", ";
    queryString += QString::number((int) chapter.getAvailability());
    queryString += ");";

    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
    } else {
        response.code = Fail;
        qDebug() << "Error while adding chapter: " << query.lastError().text();
        return response;
    }

    // if that doesn't work, use query "select seq from sqlite_sequence where name="table_name""
    qint32 lastInsertId = query.lastInsertId().toInt();
    *newId = lastInsertId;

    queryString = "insert into Chapter (item_id, textbook_id, chapter_num) values (";
    queryString += QString::number(lastInsertId) + ", ";
    queryString += QString::number(chapter.getParentTextbookId()) + ", ";
    queryString += QString::number(chapter.getChapterNumber()) + ");";

    if (!result) {
        qDebug() << "Error while adding chapter info: " << query.lastError().text();
    }

    for (Section* s : chapter.getSectionList())
    {
        addSection(sessionID, *s, &lastInsertId);
    }

    return response;
}

ServerResponse Server::addSection(QUuid sessionID, Section& section, qint32* newId)
{
    ServerResponse response;
    response.sessionID = sessionID;
    QSqlQuery query;

    // TODO: ensure that getParentChapterId() belongs to getParentTextbookId().


    QString queryString = "insert into SellableItem (name, price_cents, available) values (";
    queryString += "\"" + section.getName() + "\", ";
    queryString += QString::number(section.getPriceCents()) + ", ";
    queryString += QString::number((int) section.getAvailability());
    queryString += ");";

    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
    } else {
        response.code = Fail;
        qDebug() << "Error while adding section: " << query.lastError().text();
        return response;
    }

    // if that doesn't work, use query "select seq from sqlite_sequence where name="table_name""
    qint32 lastInsertId = query.lastInsertId().toInt();
    *newId = lastInsertId;

    queryString = "insert into Section (item_id, chapter_id, section_num) values (";
    queryString += QString::number(lastInsertId) + ", ";
    queryString += QString::number(section.getParentChapterId()) + ", ";
    queryString += QString::number(section.getSectionNumber()) + ");";

    if (!result) {
        qDebug() << "Error while adding Section info: " << query.lastError().text();
    }

    return response;
}

ServerResponse Server::replaceCourse(QUuid sessionID, qint32 id, Course& c)
{
    // TODO: Implement
    ServerResponse response;
    response.sessionID = sessionID;
    response.code = Fail;
    return response;
}

ServerResponse Server::replaceTextbook(QUuid sessionID, qint32 id, Textbook& c)
{
    // TODO: Implement
    ServerResponse response;
    response.sessionID = sessionID;
    response.code = Fail;
    return response;
}

ServerResponse Server::replaceChapter(QUuid sessionID, qint32 id, Chapter& c)
{
    // TODO: Implement
    ServerResponse response;
    response.sessionID = sessionID;
    response.code = Fail;
    return response;
}

ServerResponse Server::replaceSection(QUuid sessionID, qint32 id, Section& c)
{
    // TODO: Implement
    ServerResponse response;
    response.sessionID = sessionID;
    response.code = Fail;
    return response;
}

ServerResponse Server::registerStudentUser(QUuid sessionID, Student& usr, QString pwd, qint32* id)
{
    ServerResponse response;
    response.sessionID = sessionID;
    QSqlQuery query;
    SecurityUtils security;

    // Make password hash
    QString hash = security.makePasswordHash(usr.getUsername(), pwd);

    QString queryString = "insert into User (username, name, password, role) values (\"" +
            usr.getUsername() + "\", \"" + usr.getName() + "\", \"" +
            hash + "\", " + QString::number(2) + ");";

    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
    } else {
        response.code = Fail;
        qDebug() << "Error while adding user: " << query.lastError().text();
        return response;
    }

    // if that doesn't work, use query "select seq from sqlite_sequence where name="table_name""
    qint32 lastInsertId = query.lastInsertId().toInt();

    queryString = "insert into Student (user_id, student_num, email) values (" +
            QString::number(lastInsertId) + ", \""
            + usr.getStudentNumber() + "\", \"" + usr.getEmailAddress() + "\");";

    result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
        *id = lastInsertId;
    } else {
        response.code = Fail;
        qDebug() << "Error while adding student user: " << query.lastError().text();
        return response;
    }

    if (usr.getDeliveryInfo()) {
        queryString = "insert into DeliveryInfo (user_id, email) values (" +
                QString::number(lastInsertId) + ", \"" +
                usr.getDeliveryInfo()->getEmailAddress() + "\");";

        result = dbManager->runQuery(queryString, &query);

        if (!result) {
            qDebug() << "Error while adding delivery info: " << query.lastError().text();
        }
    }

    if (usr.getCreditCardInfo()) {
        queryString = "insert into CreditCardInfo " \
                "(user_id, holder_name, number, expiry_date, security_code) values (" +
                QString::number(lastInsertId) + ", \"" +
                usr.getCreditCardInfo()->getCardholderName() + "\", \"" +
                usr.getCreditCardInfo()->getCardNumber() + "\", \"" +
                usr.getCreditCardInfo()->getExpiry() + "\", \"" +
                usr.getCreditCardInfo()->getSecurityCode() + "\");";

        result = dbManager->runQuery(queryString, &query);

        if (!result) {
            qDebug() << "Error while adding billing info: " << query.lastError().text();
        }
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
                        "<not implemented: Server.cpp:389>",
                        "<not implemented: Server.cpp:390>",
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

bool Server::validateBillingInfo(const BillingInfo *billingInfo)
{
    if (billingInfo == nullptr)
        return false;

    // Could potentially call a validator API from the billing system
    return true;
}

bool Server::validateDeliveryInfo(const DeliveryInfo *deliveryInfo)
{
    if (deliveryInfo == nullptr)
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

    if (! order.getItems()->size() > 0) {
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


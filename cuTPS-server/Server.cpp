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
        openSessions.insert(id, -1);
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

    int numRemoved = openSessions.remove(sessionID);

    if (numRemoved > 0) {
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
    QString queryString = "select id, password, role from User where username = \""
            + creds.username + "\";";

    bool result = dbManager->runQuery(queryString,
                                      &query);

    if (result) {
        if (query.first()) {
            QString hash = query.value(1).toString();
            bool success = security.validatePassword(creds.username,
                                                     creds.password,
                                                     hash);
            if (success) {
                response.code = Success;
                int uRole = query.value(2).toInt();

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

                //update openSessions to indicate that this session belongs to
                // authenticated user
                openSessions.insert(sessionID, query.value(0).toInt());

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

ServerResponse Server::getSessionRole(QUuid sessionID, Role& userRole)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;

    int userID = openSessions.value(sessionID, -1);

    if (userID < 0) {
        response.code = Fail;
        response.message = "session not found or doesn't have associated user";
        return response;
    }

    QString queryString = "select role from User where id = " + QString::number(userID) + ";";

    bool result = dbManager->runQuery(queryString,
                                      &query);

    if (result) {
        if (query.first()) {
            response.code = Success;
            int uRole = query.value(0).toInt();

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
        response.message = query.lastError().text();

        qDebug() << "Failed to auth user: " << response.message;
        response.code = Fail;
    }

    return response;
}

ServerResponse Server::getSessionUserId(QUuid sessionID, int& userID)
{
    ServerResponse response;
    response.sessionID = sessionID;

    int id = openSessions.value(sessionID, -1);

    if (id < 0) {
        response.code = Fail;
        response.message = "session not found or doesn't have associated user";
        return response;
    }

    userID = id;

    response.code = Success;
    return response;
}

ServerResponse Server::addCourse(QUuid sessionID, Course& course, qint32& newId)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;

    QString queryString;

    if (course.getTermSection().size() < 1) {
        queryString = "insert into Course (code, name, term_section, term_year) values (\"" +
            course.getCourseCode() + "\", \"" +
            course.getCourseName() + "\", \"\", " +
            QString::number(course.getTermYear()) + ");";
    }
    else {
        queryString = "insert into Course (code, name, term_section, term_year) values (\"" +
            course.getCourseCode() + "\", \"" +
            course.getCourseName() + "\", \"" +
            course.getTermSection().at(0) + "\", " +
            QString::number(course.getTermYear()) + ");";
    }


    qDebug() << "About to insert Course, query'"
             << queryString << "'";

    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
        response.message = "";
        newId = query.lastInsertId().toInt();
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
        queryString += QString::number(course.getId());
        queryString += ", ";
        queryString += QString::number(textbookId);
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

ServerResponse Server::addTextbook(QUuid sessionID, Textbook& textbook, qint32& newId)
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
        newId = query.lastInsertId().toInt();
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();

        qDebug() << "Server::addTextbook Failed to insert into SellableItem: "
                 << response.message;
        return response;
    }

    queryString = "insert into Textbook (edition, authors, isbn) values (\"" +
                  textbook.getEdition() + "\", \"" +
                  textbook.getAuthors() + "\", \"" +
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
        addChapter(sessionID, *c, stub);
    }

    return response;
}

ServerResponse Server::addChapter(QUuid sessionID, Chapter& chapter, qint32& newId)
{
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
        newId = query.lastInsertId().toInt();
    } else {
        response.code = Fail;
        qDebug() << "Error while adding chapter: " << query.lastError().text();
        return response;
    }

    queryString = "insert into Chapter (item_id, textbook_id, chapter_num) values (";
    queryString += QString::number(newId) + ", ";
    queryString += QString::number(chapter.getParentTextbookId()) + ", ";
    queryString += QString::number(chapter.getChapterNumber()) + ");";

    result = dbManager->runQuery(queryString, &query);

    if (!result) {
        qDebug() << "Error while adding chapter info: " << query.lastError().text();
    }

    qint32 lastInsertId;

    for (Section* s : chapter.getSectionList())
    {
        addSection(sessionID, *s, lastInsertId);
    }

    return response;
}

ServerResponse Server::addSection(QUuid sessionID, Section& section, qint32& newId)
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
        newId = query.lastInsertId().toInt();
    } else {
        response.code = Fail;
        qDebug() << "Error while adding section: " << query.lastError().text();
        return response;
    }

    queryString = "insert into Section (item_id, chapter_id, section_num) values (";
    queryString += QString::number(newId) + ", ";
    queryString += QString::number(section.getParentChapterId()) + ", ";
    queryString += QString::number(section.getSectionNumber()) + ");";

    result = dbManager->runQuery(queryString, &query);

    if (!result) {
        qDebug() << "Error while adding Section info: " << query.lastError().text();
    }

    return response;
}

ServerResponse Server::replaceCourse(QUuid sessionID, qint32 id, Course& course)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;

    QString queryString = "";
    queryString += "update Course set ";
    queryString += "code = \"" + course.getCourseCode() + "\", ";
    queryString += "name = \"" + course.getCourseName() + "\", ";
    queryString += "termSection = \"" + QString(course.getTermSection().at(0)) + "\", ";
    queryString += "termYear = " + QString::number(course.getTermYear()) + " ";
    queryString += "where id = " + QString::number(id) + ";";

    qDebug() << "About to replace Course, query'"
             << queryString << "'";

    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();

        qDebug() << "Failed to replace course: " << response.message;
        return response;
    }

    return response;
}

ServerResponse Server::replaceTextbook(QUuid sessionID, qint32 id, Textbook& textbook)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;

    QString queryString = "";
    queryString += "update SellableItem set ";
    queryString += "name = \"" + textbook.getName() + "\", ";
    queryString += "price_cents = " + QString::number(textbook.getPriceCents()) + ", ";
    queryString += "available = " + QString::number(textbook.getAvailability()? 1 : 0) + " ";
    queryString += "where id = " + QString::number(id) + ";";

    qDebug() << "About to replace SellableItem, query'"
             << queryString << "'";

    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();

        qDebug() << "Failed to replace SellableItem: " << response.message;
        return response;
    }

    queryString = "";
    queryString += "update Textbook set ";
    queryString += "edition = \"" + textbook.getEdition() + "\", ";
    queryString += "authors = \"" + textbook.getAuthors() + "\", ";
    queryString += "isbn = \"" + textbook.getISBN() + "\" ";
    queryString += "where item_id = " + QString::number(id) + ";";

    qDebug() << "About to replace Textbook, query'"
             << queryString << "'";

    result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();

        qDebug() << "Failed to replace Textbook: " << response.message;
        return response;
    }

    return response;
}

ServerResponse Server::replaceChapter(QUuid sessionID, qint32 id, Chapter& chapter)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;

    QString queryString = "";
    queryString += "update SellableItem set ";
    queryString += "name = \"" + chapter.getName() + "\", ";
    queryString += "price_cents = " + QString::number(chapter.getPriceCents()) + ", ";
    queryString += "available = " + QString::number(chapter.getAvailability()? 1 : 0) + " ";
    queryString += "where id = " + QString::number(id) + ";";

    qDebug() << "About to replace SellableItem, query'"
             << queryString << "'";

    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();

        qDebug() << "Failed to replace SellableItem: " << response.message;
        return response;
    }

    queryString = "";
    queryString += "update Chapter set ";
    queryString += "chapter_num = " + QString::number(chapter.getChapterNumber()) + " ";
    queryString += "where item_id = " + QString::number(id) + ";";

    qDebug() << "About to replace Chapter, query'"
             << queryString << "'";

    result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();

        qDebug() << "Failed to replace Chapter: " << response.message;
        return response;
    }

    return response;
}

ServerResponse Server::replaceSection(QUuid sessionID, qint32 id, Section& section)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;

    QString queryString = "";
    queryString += "update SellableItem set ";
    queryString += "name = \"" + section.getName() + "\", ";
    queryString += "price_cents = " + QString::number(section.getPriceCents()) + ", ";
    queryString += "available = " + QString::number(section.getAvailability()? 1 : 0) + " ";
    queryString += "where id = " + QString::number(id) + ";";

    qDebug() << "About to replace SellableItem, query'"
             << queryString << "'";

    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();

        qDebug() << "Failed to replace SellableItem: " << response.message;
        return response;
    }

    queryString = "";
    queryString += "update Section set ";
    queryString += "section_num = " + QString::number(section.getSectionNumber()) + " ";
    queryString += "where item_id = " + QString::number(id) + ";";

    qDebug() << "About to replace Section, query'"
             << queryString << "'";

    result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();

        qDebug() << "Failed to replace Section: " << response.message;
        return response;
    }

    return response;
}

ServerResponse Server::removeCourse(QUuid sessionID, qint32 id)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;

    QString queryString = "";
    queryString += "delete from Course where id = ";
    queryString += QString::number(id);
    queryString += ";";

    qDebug() << "About to delete Course, query'"
             << queryString << "'";

    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();

        qDebug() << "Failed to delete course: " << response.message;
        return response;
    }

    return response;
}

ServerResponse Server::removeSellableItem(QUuid sessionID, qint32 id)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;

    QString queryString = "";
    queryString += "delete from SellableItem where id = ";
    queryString += QString::number(id);
    queryString += ";";

    qDebug() << "About to delete SellableItem, query'"
             << queryString << "'";

    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        response.code = Success;
        response.message = "";
    }
    else {
        response.code = Fail;
        response.message = query.lastError().text();

        qDebug() << "Failed to delete SellableItem: " << response.message;
        return response;
    }

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

ServerResponse Server::getAllTextbooks(QUuid sessionID, QVector<Textbook> &textbooks)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;

    QString queryString = "";
    queryString += "SELECT id, name, edition, authors, price_cents, available, isbn ";
    queryString += "FROM Textbook tb JOIN SellableItem s ";
    queryString += "ON (s.id = tb.item_id); ";

    qDebug() << "query string: '" << queryString << "'";
    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        qDebug() << "Query for all texts successful. Rows: " << query.size();

        while(query.next()) {
            Textbook* textbook = new Textbook(query.value(0).toInt(),
                                             query.value(1).toString(),
                                             query.value(2).toString(),
                                             query.value(3).toString(),
                                             query.value(4).toInt(),
                                             query.value(5).toBool(),
                                             query.value(6).toString());
            textbooks.append(*textbook);
        }

        response.code = Success;
        response.message = "";
    }
    else {
        qDebug() << "Query for all texts failed.";

        response.code = Fail;
        response.message = query.lastError().text();
    }

    return response;
}

ServerResponse Server::getAllCourses(QUuid sessionID, QVector<Course>& courses)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;

    QString queryString = "";
    queryString += "select id, code, name, term_section, term_year from Course;";

    qDebug() << "query string: '" << queryString << "'";
    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        qDebug() << "Query for all courses successful. Rows: " << query.size();

        while(query.next()) {
            Course* course = new Course(query.value(0).toInt(),
                                        query.value(1).toString(),
                                        query.value(2).toString(),
                                        query.value(3).toString(),
                                        query.value(4).toInt());
            qDebug() << "course row with id="
                     << QString::number(course->getId());
            courses.append(*course);
        }

        response.code = Success;
        response.message = "";
    }
    else {
        qDebug() << "Query for all courses failed.";

        response.code = Fail;
        response.message = query.lastError().text();
    }

    return response;
}

ServerResponse Server::getStudentCourses(QUuid sessionID, const int& userID, QVector<Course>& courses)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;

    QString queryString = "";
    queryString += "select Course.id, Course.code, Course.name, Course.termSection, Course.termYear ";
    queryString += "from User join User_Course on User.id = User_Course.user_id ";
    queryString += "where User.id = ";
    queryString += QString::number(userID);
    queryString += ";";

    qDebug() << "query string: '" << queryString << "'";
    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        qDebug() << "Query for registered courses successful. Rows: " << query.size();

        while(query.next()) {
            Course* course = new Course(query.value(0).toInt(),
                                       query.value(1).toString(),
                                       query.value(2).toString(),
                                       query.value(3).toString(),
                                       query.value(4).toInt());
            courses.append(*course);
        }

        response.code = Success;
        response.message = "";
    }
    else {
        qDebug() << "Query for registered courses failed.";

        response.code = Fail;
        response.message = query.lastError().text();
    }

    return response;
}

ServerResponse Server::getRequiredTextbooks(QUuid sessionID,const int& userID, QVector<int>* textbookIDs)
{
    ServerResponse response;
    response.sessionID = sessionID;

    QSqlQuery query;

    QString queryString = "";
    queryString += "select Course_Textbook.textbook_id from User ";
    queryString += "join User_Course on User.id = User_Course.user_id ";
    queryString += "join Course_Textbook on User_Course.course_id = Course_Textbook.course_id ";
    queryString += "where User.id = ";
    queryString += QString::number(userID);
    queryString += ";";

    qDebug() << "query string: '" << queryString << "'";
    bool result = dbManager->runQuery(queryString, &query);

    if (result) {
        qDebug() << "Query for required texts successful. Rows: " << query.size();

        while(query.next()) {
            textbookIDs->append(query.value(0).toInt());
        }

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
    queryString += "select Textbook.item_id, Textbook.edition, Textbook.authors, Textbook.isbn, ";
    queryString += "SellableItem.name, SellableItem.price_cents, ";
    queryString += "SellableItem.available from Textbook inner join SellableItem on id=item_id ";
    queryString += "where Textbook.item_id = ";
    queryString += QString::number(textbookID);
    queryString += ";";

    qDebug() << "getBookDetails query string: '" << queryString << "'";

    bool result = dbManager->runQuery(queryString, &query);

    qDebug() << "query result: " << result;

    // TODO : Handle case where attributes are null
    if (result) {
        bool found = false;
        while(query.next()) {
            found = true;
            // TODO: remove this debug log
            qDebug() << "Get Book Details("
                     << query.value(0).toInt() << ", "
                     << query.value(1).toString() << ", "
                     << query.value(2).toInt() << ", "
                     << query.value(3).toBool() << ", "
                     << query.value(4).toString() << ")";

            *textbook = new Textbook(
                        query.value(0).toInt(),
                        query.value(1).toString(),
                        query.value(2).toString(),
                        query.value(3).toString(),
                        query.value(4).toString(),
                        query.value(5).toInt(),
                        query.value(6).toBool()
                        );
        }

        if (found) {
            response.code = Success;
            response.message = "";
        }
        else {
            //textbook with given ID not found
            *textbook = new Textbook();

            response.code = Fail;
            response.message = "textbook with given ID not found";
        }
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


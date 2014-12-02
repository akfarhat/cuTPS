#include "Storage.h"

Storage::Storage(QObject *parent) :
    QObject(parent)
{
    dbManager = new DatabaseManager();

    if (!dbManager->openDB()) {
        throw dbManager->getLastError();
    }
}

bool Storage::getUserRole(int userID, Role& userRole)
{
    QSqlQuery query;
    query.prepare("select * from Student " +
                  "where user_id = :id");
    query.bindValue(":id", userID);
    bool result = dbManager->runQuery(&query);

    if (result && query.first()) {
        userRole = Role::Student;
        return true;
    }

    query.prepare("select * from ContentManager " +
                  "where user_id = :id");
    query.bindValue(":id", userID);
    bool result = dbManager->runQuery(&query);

    if (result && query.first()) {
        userRole = Role::ContentManager;
        return true;
    }

    query.prepare("select * from Administrator " +
                  "where user_id = :id");
    query.bindValue(":id", userID);
    bool result = dbManager->runQuery(&query);

    if (result && query.first()) {
        userRole = Role::Administrator;
        return true;
    }

    return false;
}

bool Storage::getUser(QString username, QString password, User& user, Role& userRole)
{
    QSqlQuery query;
    query.prepare("select id, name, username from User " +
                  "where username = :username " +
                  "and password = :password ");
    query.bindValue(":username", username);
    query.bindValue(":password", password);
    bool result = dbManager->runQuery(&query);

    if (result) {
        if (query.first()) {
           user = new User(query.value(0),
                           query.value(1),
                           query.value(2));
           userRole = getUserRole(query.value(0));
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

}



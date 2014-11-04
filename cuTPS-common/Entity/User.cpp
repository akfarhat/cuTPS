#include "User.h"

User::User(int id, QString n, QString u) : userId(id), name(n), username(u) {

}

User::~User() {}

int User::getUserId() {
    return userId;
}

void User::setUserId(int newId) {
    userId = newId;
}

QString User::getUsername() {
    return username;
}

void User::setUsername(QString newUsername) {
    username = newUsername;
}

QString User::getName() {
    return name;
}

void User::setName(QString newName) {
    name = newName;
}

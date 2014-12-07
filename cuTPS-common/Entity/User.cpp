#include "User.h"

User::User(QString name, QString uname)
    : name(name), username(uname), role(None)
{}

User::User(int id, QString n, QString u)
    : userId(id), name(n), username(u), role(None)
{}

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

QString User::getDetails()
{

}

Role User::getRole() const
{
    return role;
}

void User::setRole(const Role value)
{
    role = value;
}


#include "User.h"

User::User(QString name, QString uname)
    : name(name), username(uname)
{}

User::User(int id, QString n, QString u)
    : userId(id), name(n), username(u)
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

QDataStream& operator<<(QDataStream& os, const User& u)
{
    os.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    os << u.userId
       << u.username
       << u.name;

    return os;
}

QDataStream& operator>>(QDataStream& is, User& u)
{
    is.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    is >> u.userId
       >> u.username
       >> u.name;

    return is;
}

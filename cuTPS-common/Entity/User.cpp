#include "User.h"

User::User(QString n, QString u) : name(n), username(u) {

}

User::~User() {}

int User::getUserId() {
    return userId;
}

QString User::getUsername() {
    return username;
}

QString User::getName() {
    return name;
}

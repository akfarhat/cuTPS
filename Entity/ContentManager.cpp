#include "ContentManager.h"

ContentManager::ContentManager(QString name, QString username) : User(name, username) {

}

ContentManager::~ContentManager() {}

QString ContentManager::getEmailAddress() {
    return emailAddress;
}

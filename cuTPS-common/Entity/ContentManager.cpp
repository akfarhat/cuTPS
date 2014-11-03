#include "ContentManager.h"

ContentManager::ContentManager(int id, QString name, QString username) : User(id, name, username) {

}

ContentManager::~ContentManager() {}

QString ContentManager::getEmailAddress() {
    return emailAddress;
}

void ContentManager::setEmailAddress(QString newEmail) {
    emailAddress = newEmail;
}

QString ContentManager::getDetails() {
    QString details = "";
    details += "Type: Content Manager\nUser ID: ";
    details += QString::number(this->getUserId());
    details += "\nUsername: ";
    details += this->getUsername();
    details += "\nName: ";
    details += this->getName();
    details += "\nEmail Address: ";
    details += this->getEmailAddress();
    details += "\n";

    return details;
}

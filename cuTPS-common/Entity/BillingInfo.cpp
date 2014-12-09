#include "BillingInfo.h"

BillingInfo::BillingInfo()
{
}

BillingInfo::BillingInfo(QString name, QString email, QString addr, QString number) {
    billingName    = name;
    emailAddress   = email;
    billingAddress = addr;
    phoneNumber    = number;
}

// Setters

void BillingInfo::setEmail(QString email) {
    emailAddress = email;
}

void BillingInfo::setBillingAddress(QString addr) {
    billingAddress = addr;
}

void BillingInfo::setPhoneNumber(QString number) {
    phoneNumber = number;
}

void BillingInfo::setName(QString name) {
    billingName = name;
}

// Getters

QString BillingInfo::getEmail() {
    return emailAddress;
}

QString BillingInfo::getBillingAddress() {
    return billingAddress;
}

QString BillingInfo::getPhoneNumber() {
    return phoneNumber;
}

QString BillingInfo::getName() {
    return billingName;
}

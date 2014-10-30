#include "DeliveryInfo.h"

DeliveryInfo::DeliveryInfo(QString email) : emailAddress(email) {

}

DeliveryInfo::~DeliveryInfo() {}


QString DeliveryInfo::getEmailAddress() {
    return emailAddress;
}

void DeliveryInfo::setEmailAddress(QString newEmail) {
    emailAddress = newEmail;
}


#include "DeliveryInfo.h"

DeliveryInfo::DeliveryInfo(QString email) : emailAddress(email) {

}

DeliveryInfo::~DeliveryInfo() {}


QString DeliveryInfo::getEmailAddress() {
    return emailAddress;
}


#include "DeliveryInfo.h"

DeliveryInfo::DeliveryInfo(email) : emailAddress(email) {

}

DeliveryInfo::~DeliveryInfo() {}


QString DeliveryInfo::getEmailAddress() {
    return emailAddress;
}


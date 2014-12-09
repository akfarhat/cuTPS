#include "DeliveryInfo.h"
#include "Defines.h"

DeliveryInfo::DeliveryInfo()
{}

DeliveryInfo::DeliveryInfo(QString email) : emailAddress(email) {

}

DeliveryInfo::~DeliveryInfo() {}


QString DeliveryInfo::getEmailAddress() const {
    return emailAddress;
}

void DeliveryInfo::setEmailAddress(QString newEmail) {
    emailAddress = newEmail;
}

QDataStream& operator<<(QDataStream& os, const DeliveryInfo& d)
{
    os.setVersion(TPSNetProtocolDef::PROTOCOL_VER);
    os << d.emailAddress;
    return os;
}

QDataStream& operator>>(QDataStream& is, DeliveryInfo& d)
{
    is.setVersion(TPSNetProtocolDef::PROTOCOL_VER);
    is >> d.emailAddress;
    return is;
}

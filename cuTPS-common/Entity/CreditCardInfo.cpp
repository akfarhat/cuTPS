#include "CreditCardInfo.h"
#include "Defines.h"

CreditCardInfo::CreditCardInfo()
{
}

CreditCardInfo::CreditCardInfo(QString name, QString email, QString addr, QString pnumber,
                               QString cholder, QString cnumber, QString expiry, QString sCode)
                               : BillingInfo(name, email, addr, pnumber)
{
    cardholder = cholder;
    number = cnumber;
    expiryDate = expiry;
    securityCode = sCode;
}

QString CreditCardInfo::getCardholderName() {
    return cardholder;
}

void CreditCardInfo::setCardholder(QString newcholder) {
    cardholder = newcholder;
}

QString CreditCardInfo::getCardNumber() {
    return number;
}

void CreditCardInfo::setCardNumber(QString newNumber) {
    number = newNumber;
}

QString CreditCardInfo::getExpiry() {
    return expiryDate;
}

void CreditCardInfo::setExpiry(QString newExpiry) {
    expiryDate = newExpiry;
}

QString CreditCardInfo::getSecurityCode() {
    return securityCode;
}

void CreditCardInfo::setSecurityCode(QString newCode) {
    securityCode = newCode;
}

QString CreditCardInfo::getPaymentDetails() const {
    QString paymentStr = QString("%1|%2|%3|%4|%5|%6|%7|%8")
            .arg(number, expiryDate, securityCode,
                 cardholder, billingName, billingAddress,
                 emailAddress, phoneNumber);
    return paymentStr;
}

CreditCardInfo* CreditCardInfo::clone() const
{
    return new CreditCardInfo(*this);
}

// TODO: add basic text encryption
QDataStream& operator<<(QDataStream& os, const CreditCardInfo& d)
{
    os.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    os << d.billingName
       << d.billingAddress
       << d.emailAddress
       << d.phoneNumber
       << d.cardholder
       << d.number
       << d.expiryDate
       << d.securityCode;

    return os;
}

QDataStream& operator>>(QDataStream& is, CreditCardInfo& d)
{
    is.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    is >> d.billingName
       >> d.billingAddress
       >> d.emailAddress
       >> d.phoneNumber
       >> d.cardholder
       >> d.number
       >> d.expiryDate
       >> d.securityCode;

    return is;
}


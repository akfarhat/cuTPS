#include "CreditcardInfo.h"

CreditCardInfo::CreditCardInfo(QString name, QString email, QString addr, QString pnumber,
                               QString ctype, QString cnumber, QString expiry, QString sCode)
                               : BillingInfo(name, email, addr, pnumber) {
    type = ctype;
    number = cnumber;
    expiryDate = expiry;
    securityCode = sCode;
}

QString CreditCardInfo::getCardType() {
    return type;
}

void CreditCardInfo::setCardType(QString newCardType) {
    type = newCardType;
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

QString CreditCardInfo::getPaymentDetails() {
    return QString( type + ": " + billingName + "|"
                  + number + "|" + securityCode + "|"
                  + expiryDate );
}

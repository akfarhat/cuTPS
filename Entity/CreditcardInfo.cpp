#include "CreditcardInfo.h"

CreditCardInfo::CreditCardInfo(QString name, QString email, QString addr, QString pnumber,
                               QString provider, QString cnumber, QString expiry, QString sCode)
                               : BillingInfo(name, email, addr, pnumber) {
    cardProvider = provider;
    cardNumber = cnumber;
    cardExpiry = expiry;
    securityCode = sCode;
}

QString CreditCardInfo::getProvider() {
    return cardProvider;
}

void CreditCardInfo::setProvider(QString newProvider) {
    cardProvider = newProvider;
}

QString CreditCardInfo::getCardNumber() {
    return cardNumber;
}

void CreditCardInfo::setCardNumber(QString newNumber) {
    cardNumber = newNumber;
}

QString CreditCardInfo::getExpiry() {
    return cardExpiry;
}

void CreditCardInfo::setExpiry(QString newExpiry) {
    cardExpiry = newExpiry;
}

QString CreditCardInfo::getPaymentDetails() {
    return QString( cardProvider + ": " + billingName + "|"
                  + cardNumber + "|" + securityCode + "|"
                  + cardExpiry );
}

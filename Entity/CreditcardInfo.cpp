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

QString CreditCardInfo::getCardNumber() {
    return cardNumber;
}

QString CreditCardInfo::getExpiry() {
    return cardExpiry;
}

QString CreditCardInfo::getPaymentDetails() {
    return QString( cardProvider + ": " + billingName + "|"
                  + cardNumber + "|" + securityCode + "|"
                  + cardExpiry );
}

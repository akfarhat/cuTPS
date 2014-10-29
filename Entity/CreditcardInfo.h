#ifndef CREDITCARDINFO_H
#define CREDITCARDINFO_H

#include <QString>
#include "BillingInfo.h"

class CreditCardInfo : public BillingInfo {

    public:
        CreditCardInfo(QString name, QString email, QString addr, QString pnumber,
                       QString provider, QString cnumber, QString expiry, QString sCode);
        QString getProvider();
        QString getCardNumber();
        QString getExpiry();
        QString getPaymentInfo();

    private:
        QString cardProvider;
        QString cardNumber;
        QString cardExpiry;
        QString securityCode;
};

#endif // CREDITCARDINFO_H

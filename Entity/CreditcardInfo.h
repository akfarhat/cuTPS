#ifndef CREDITCARDINFO_H
#define CREDITCARDINFO_H

#include <QString>
#include "BillingInfo.h"

class CreditCardInfo : public BillingInfo {

    private:
        QString cardProvider;
        QString cardNumber;
        QString cardExpiry;
        QString securityCode;

    public:
        CreditCardInfo(QString name, QString email, QString addr, QString pnumber,
                       QString provider, QString cnumber, QString expiry, QString sCode);

        QString getProvider();
        void setProvider(QString);
        QString getCardNumber();
        void setCardNumber(QString);
        QString getExpiry();
        void setExpiry(QString);

        virtual QString getPaymentDetails();

};

#endif // CREDITCARDINFO_H

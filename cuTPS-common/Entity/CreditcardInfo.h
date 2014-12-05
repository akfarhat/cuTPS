// Class: CreditCardInfo
// Type: Entity
// Description:
//     Concrete class containing the actual payment
//     details that a user can use to purchase content


#ifndef CREDITCARDINFO_H
#define CREDITCARDINFO_H

#include <QString>
#include "BillingInfo.h"

class CreditCardInfo : public BillingInfo {

    private:
        QString type;
        QString number;
        QString expiryDate;
        QString securityCode;

    public:
        CreditCardInfo(QString name, QString email, QString addr, QString pnumber,
                       QString ctype, QString cnumber, QString expiry, QString sCode);

        QString getCardType();
        void setCardType(QString);
        QString getCardNumber();
        void setCardNumber(QString);
        QString getExpiry();
        void setExpiry(QString);
        QString getSecurityCode();
        void setSecurityCode(QString);

        virtual QString getPaymentDetails();

};

#endif // CREDITCARDINFO_H

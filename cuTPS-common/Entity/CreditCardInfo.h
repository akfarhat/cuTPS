// Class: CreditCardInfo
// Type: Entity
// Description:
//     Concrete class containing the actual payment
//     details that a user can use to purchase content


#ifndef CREDITCARDINFO_H
#define CREDITCARDINFO_H

#include "libcutps_global.h"

#include <memory>
#include <QString>

#include "BillingInfo.h"

class LIBCUTPS_EXPORT CreditCardInfo : public BillingInfo
{
public:
    CreditCardInfo(QString name, QString email, QString addr, QString pnumber,
                   QString cholder, QString cnumber, QString expiry, QString sCode);
    virtual inline ~CreditCardInfo() {}
    QString getCardholderName();
    void setCardholder(QString);
    QString getCardNumber();
    void setCardNumber(QString);
    QString getExpiry();
    void setExpiry(QString);
    QString getSecurityCode();
    void setSecurityCode(QString);

    virtual QString getPaymentDetails() const;
    virtual CreditCardInfo* clone() const;

private:
    // QString type; >> no need; it is very easy to determine card type by its number
    QString cardholder; // this might be different from name in BillingInfo.
    QString number;
    QString expiryDate; // TODO: make it month+year pair
    QString securityCode;
};

#endif // CREDITCARDINFO_H

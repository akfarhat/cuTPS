// Class: BillingInfo
// Type: Entity
// Description:
//     Abstract class representing billing information for
//     a student user

#ifndef BILLINGINFO_H
#define BILLINGINFO_H

#include "libcutps_global.h"

#include <memory>
#include <QString>

class LIBCUTPS_EXPORT BillingInfo
{
public:
    BillingInfo(QString name, QString email, QString addr, QString number);
    virtual inline ~BillingInfo() {}
    // This string will represent the information required to
    // charge this user.
    virtual QString getPaymentDetails() const = 0;
    virtual BillingInfo* clone() const  = 0;

    // Setters and getters
    void setEmail(QString email);
    void setBillingAddress(QString addr);
    void setPhoneNumber(QString number);
    void setName(QString name);
    QString getEmail();
    QString getBillingAddress(); // TODO: Make city, state/prov, postal code separate
    QString getPhoneNumber();
    QString getName();

protected:
    QString billingName;
    QString emailAddress;
    QString billingAddress;
    QString phoneNumber;
};

#endif // BILLINGINFO_H

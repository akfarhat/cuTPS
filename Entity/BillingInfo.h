#ifndef BILLINGINFO_H
#define BILLINGINFO_H

#include <QString>

class BillingInfo {

    public:
        BillingInfo(QString name, QString email, QString addr, QString number);

        // This string will represent the information required to
        // charge this user.
        virtual QString getPaymentDetails() = 0;

        // Setters and getters
        void setEmail(QString email);
        void setBillingAddress(QString addr);
        void setPhoneNumber(QString number);
        void setName(QString name);
        QString getEmail();
        QString getBillingAddress();
        QString getPhoneNumber();
        QString getName();

    protected:
        QString billingName;
        QString emailAddress;
        QString billingAddress;
        QString phoneNumber;
};

#endif // BILLINGINFO_H

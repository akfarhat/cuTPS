// Class: DeliveryInfo
// Type: Entity
// Description:
//     Entity object representing delivery details that
//     for a particular order by a student user


#ifndef DELIVERYINFO_H
#define DELIVERYINFO_H

#include <QString>

class DeliveryInfo {
    private:
        QString emailAddress;

    public:
        DeliveryInfo(QString);
        ~DeliveryInfo();
        QString getEmailAddress();
        void setEmailAddress(QString);

};

#endif // DELIVERYINFO_H

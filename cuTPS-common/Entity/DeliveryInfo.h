// Class: DeliveryInfo
// Type: Entity
// Description:
//     Entity object representing delivery details that
//     for a particular order by a student user


#ifndef DELIVERYINFO_H
#define DELIVERYINFO_H

#include <QString>

class DeliveryInfo
{
private:
    QString emailAddress;

public:
    DeliveryInfo();
    DeliveryInfo(QString);
    ~DeliveryInfo();
    QString getEmailAddress() const;
    void setEmailAddress(QString);


    // Serialization routines
    friend QDataStream& operator<<(QDataStream& os, const DeliveryInfo& d); // output
    friend QDataStream& operator>>(QDataStream& is, DeliveryInfo& d); // input
};

#endif // DELIVERYINFO_H

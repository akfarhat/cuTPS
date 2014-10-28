#ifndef DELIVERYINFO_H
#define DELIVERYINFO_H

#include<QString>

class DeliveryInfo {
    private:
        QString emailAddress;

    public:
        DeliveryInfo(QString);
        ~DeliveryInfo();
        QString getEmailAddress();

};

#endif // DELIVERYINFO_H

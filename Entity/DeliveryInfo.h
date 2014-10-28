#ifndef DELIVERYINFO_H
#define DELIVERYINFO_H

#include<QString>

class DeliveryInfo {
    private:
        QString emailAddress;

    public:
        DeliveryInfo(string);
        ~DeliveryInfo();
        QString getEmailAddress();

};

#endif // DELIVERYINFO_H

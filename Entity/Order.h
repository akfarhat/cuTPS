#ifndef ORDER_H
#define ORDER_H

#include <QVector>
#include "SellableItem.h"
#include "BillingInfo.h"
#include "DeliveryInfo.h"

class Order {

    public:
        Order(QVector<SellableItem*> *, BillingInfo &, DeliveryInfo &);
        ~Order();

        BillingInfo *getBillingInfo();
        DeliveryInfo *getDeliveryInfo();
        QVector<SellableItem*> getOrder();

    private:
        QVector<SellableItem*> items;
        BillingInfo &billingInfo;
        DeliveryInfo &deliveryInfo;
};

#endif // ORDER_H

// Class: Order
// Type: Entity
// Description:
//     Represents a list of items being purchased by a student user


#ifndef ORDER_H
#define ORDER_H

#include <QVector>
#include "SellableItem.h"
#include "BillingInfo.h"
#include "DeliveryInfo.h"

class Order {

    public:
        Order();
        Order(QVector<qint32>*, BillingInfo *, DeliveryInfo *);
        ~Order();

        BillingInfo *getBillingInfo() const;
        DeliveryInfo *getDeliveryInfo() const;
        QVector<qint32>* getOrder();

    private:
        QVector<qint32> itemIds;
        BillingInfo *billingInfo;
        DeliveryInfo *deliveryInfo;
};

#endif // ORDER_H

#include "Order.h"

Order::Order(QVector<qint32> *itemList, BillingInfo *billing,
             DeliveryInfo *shipping) :
    itemIds( QVector<qint32>( *itemList ) ),
    billingInfo( billing ),
    deliveryInfo( shipping )
{}

Order::~Order() {
}

BillingInfo *Order::getBillingInfo() const {
    return billingInfo;
}

DeliveryInfo *Order::getDeliveryInfo() const {
    return deliveryInfo;
}

QVector<qint32>* Order::getOrder() {
    return &itemIds;
}

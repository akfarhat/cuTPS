#include "Order.h"

Order::Order(QVector<SellableItem*> *itemList, BillingInfo &billing,
             DeliveryInfo &shipping) :
    items( QVector<SellableItem*>( *itemList ) ),
    billingInfo( billing ),
    deliveryInfo( shipping )
{}

BillingInfo *Order::getBillingInfo() {
    return &billingInfo;
}

DeliveryInfo *Order::getDeliveryInfo() {
    return &deliveryInfo;
}

QVector<SellableItem*> Order::getOrder() {
    return items;
}

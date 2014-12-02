// Class: Order
// Type: Entity
// Description:
//     Represents a list of items being purchased by a student user

#ifndef ORDER_H
#define ORDER_H

#include "SellableItem.h"

#include <QVector>
#include <QDataStream>
#include <QString>

#include "CreditCardInfo.h"
#include "DeliveryInfo.h"

class Order
{
public:
    Order();
    // Order(const Order&); // warning: there's no copy cTor here
    Order(const QVector<qint32>*, const BillingInfo*, const DeliveryInfo*);
    ~Order();

    void setBillingInfo(const BillingInfo*);
    void setDeliveryInfo(const DeliveryInfo*);
    void addItems(const QVector<qint32>&);
    void clearItems(); // same effect as getItems()->clear()

    BillingInfo* getBillingInfo() const;
    DeliveryInfo* getDeliveryInfo() const;
    QVector<qint32>* getItems();
    QString getFormattedPaymentInfo();

    friend QDataStream& operator<<(QDataStream& os, const Order& o); // output
    friend QDataStream& operator>>(QDataStream& is, Order& o); // input

private:
    QVector<qint32> itemIds;
    QString formattedPaymentInfo;   // payment info that delivery system understands
    BillingInfo* billingInfo = nullptr;
    DeliveryInfo* deliveryInfo = nullptr;
};

#endif // ORDER_H

// Class: Order
// Type: Entity
// Description:
//     Represents a list of items being purchased by a student user

#ifndef ORDER_H
#define ORDER_H

#include "libcutps_global.h"

#include "SellableItem.h"

#include <QVector>
#include <QDataStream>
#include <QString>

#include "CreditCardInfo.h"
#include "DeliveryInfo.h"

class LIBCUTPS_EXPORT Order
{
public:
    Order();
    // Order(const Order&); // warning: there's no copy cTor here
    Order(const QVector<qint32>& items,
          const BillingInfo&,
          const DeliveryInfo&);
    ~Order();

    void setBillingInfo(const BillingInfo&);
    void setDeliveryInfo(const DeliveryInfo&);
    void addItems(const QVector<qint32>& items);
    void clearItems();

    const BillingInfo* getBillingInfo() const; // may return nullptr if data is not there
    const DeliveryInfo* getDeliveryInfo() const; // may return nullptr if data is not there
    const QVector<qint32>* getItems() const; // use addItem() and clearItems() to manage items
    QString getFormattedPaymentInfo();

    friend QDataStream& operator<<(QDataStream& os, const Order& o); // output
    friend QDataStream& operator>>(QDataStream& is, Order& o); // input

private:
    QVector<qint32> itemIds;
    QString formattedPaymentInfo;   // payment info that delivery system understands
    BillingInfo* billingInfo;
    DeliveryInfo* deliveryInfo;
};

#endif // ORDER_H

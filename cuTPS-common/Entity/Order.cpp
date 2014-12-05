#include "Order.h"
#include "Defines.h"

Order::Order()
{
    billingInfo = nullptr;
    deliveryInfo = nullptr;
}

Order::Order(const QVector<qint32>& items, const BillingInfo& bi, const DeliveryInfo& di)
{
    billingInfo = nullptr;
    deliveryInfo = nullptr;
    addItems(items);
    setBillingInfo(bi);
    setDeliveryInfo(di);
}

Order::~Order()
{
    if (billingInfo) delete billingInfo;
    if (deliveryInfo) delete deliveryInfo;
}

void Order::setBillingInfo(const BillingInfo& bi)
{
    if (billingInfo) delete billingInfo;
    billingInfo = bi.clone();
}

void Order::setDeliveryInfo(const DeliveryInfo& di)
{
    if (deliveryInfo) delete deliveryInfo;
    deliveryInfo = new DeliveryInfo(di);
}

void Order::addItems(const QVector<qint32>& v)
{
    itemIds += v;
}

void Order::clearItems()
{
    itemIds.clear();
}

const BillingInfo* Order::getBillingInfo() const {
    return const_cast<const BillingInfo*>(billingInfo);
}

const DeliveryInfo* Order::getDeliveryInfo() const {
    return const_cast<const DeliveryInfo*>(deliveryInfo);
}

const QVector<qint32>* Order::getItems() const {
    return const_cast<const QVector<qint32>*>(&itemIds);
}

QString Order::getFormattedPaymentInfo()
{
    return formattedPaymentInfo;
}

QDataStream& operator<<(QDataStream& os, const Order& o)
{
    os.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

    os << *o.deliveryInfo;
    os << dynamic_cast<CreditCardInfo*>(o.billingInfo)->getPaymentDetails();
    os << static_cast<qint32>(o.itemIds.size());

    for (qint32 id : o.itemIds)
    {
        os << id;
    }

    return os;
}

QDataStream& operator>>(QDataStream& is, Order& o)
{
    is.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

    DeliveryInfo dInfo;
    QString paymentStr;
    qint32 numItems;

    is >> dInfo
       >> paymentStr
       >> numItems;

    o.setDeliveryInfo(dInfo);
    QString& pStrRef = paymentStr;
    o.formattedPaymentInfo = QString(pStrRef);
    o.clearItems();

    QVector<qint32> v(numItems);
    for (int i = 0; i < numItems; ++i)
    {
        is >> v[i];
    }

    o.addItems(v);

    return is;
}

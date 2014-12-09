#include "SellableItem.h"
#include "Defines.h"

SellableItem::SellableItem(qint32 i,
                           QString n,
                           quint32 p,
                           bool isAvailable)
    : id(i), name(n), priceCents(p), availableForSale(isAvailable)
{
}

SellableItem::SellableItem(QString n, quint32 p, bool available)
    : id(-1), name(n), priceCents(p), availableForSale(available)
{
}

SellableItem::SellableItem()
    : id (-1), name(""), priceCents(0), availableForSale(false)
{
}

SellableItem::~SellableItem() {}

qint32 SellableItem::getId() const
{
    return id;
}

void SellableItem::setId(const qint32 newId)
{
    id = newId;
}

QString SellableItem::getName() const
{
    return name;
}

void SellableItem::setName(const QString newName)
{
    name = newName;
}

quint32 SellableItem::getPriceCents() const
{
    return priceCents;
}

void SellableItem::setPriceCents(const quint32 newPriceCents)
{
    priceCents = newPriceCents;
}


bool SellableItem::getAvailability() const
{
    return availableForSale;
}

void SellableItem::setAvailability(const bool available)
{
    availableForSale = available;
}

QDataStream& operator<<(QDataStream& os, const SellableItem& i)
{
    os.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    os << i.id
       << i.name
       << i.priceCents
       << i.availableForSale;

    return os;
}

QDataStream& operator>>(QDataStream& is, SellableItem& i)
{
    is.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    is >> i.id
       >> i.name
       >> i.priceCents
       >> i.availableForSale;

    return is;
}

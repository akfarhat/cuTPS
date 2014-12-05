#include "SellableItem.h"
#include "Defines.h"

SellableItem::SellableItem(int i, QString n, int p, bool isAvailable) : id(i), name(n), priceCents(p), availableForSale(isAvailable) {
}

SellableItem::SellableItem(QString n, int p) : name(n), priceCents(p), availableForSale(false) {
}

SellableItem::SellableItem() : name(""), priceCents(0), availableForSale(false) {
}

SellableItem::~SellableItem() {}

int SellableItem::getId() const {
    return id;
}

void SellableItem::setId(const int newId) {
    id = newId;
}

QString SellableItem::getName() const {
    return name;
}

void SellableItem::setName(const QString newName) {
    name = newName;
}

int SellableItem::getPriceCents() const {
    return priceCents;
}

void SellableItem::setPriceCents(const int newPriceCents) {
    priceCents = newPriceCents;
}


bool SellableItem::getAvailability() const {
    return availableForSale;
}

void SellableItem::setAvailability(const bool available) {
    availableForSale = available;
}

QDataStream& operator<<(QDataStream& os, const SellableItem& i)
{
    os.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

    os << i.id
       << i.name
       << i.priceCents
       << i.availableForSale;

    return os;
}

QDataStream& operator>>(QDataStream& is, SellableItem& i)
{
    is.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

    qint32 id;
    QString name;
    qint32 price;
    bool isAvailable;

    is >> id
       >> name
       >> price
       >> isAvailable;

    i.setId(id);
    i.setName(name);
    i.setPriceCents(price);
    i.setAvailability(isAvailable);

    return is;
}

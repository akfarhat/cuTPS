#include "SellableItem.h"

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

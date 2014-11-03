#include "SellableItem.h"

SellableItem::SellableItem(int i, QString n, int p, bool isAvailable) : id(i), name(n), priceCents(p), availableForSale(isAvailable) {
}

SellableItem::SellableItem(QString n, int p) : name(n), price(p), availableForSale(false) {
}

SellableItem::~SellableItem() {}

int SellableItem::getId() {
    return id;
}

void SellableItem::setId(int newId) {
    id = newId;
}

QString SellableItem::getName() {
    return name;
}

void SellableItem::setName(QString newName) {
    name = newName;
}

float SellableItem::getPriceCents() {
    return price;
}

void SellableItem::setPriceCents(int newPriceCents) {
    priceCents = newPriceCents;
}


bool SellableItem::getAvailability() {
    return availableForSale;
}

void SellableItem::setAvailability(bool available) {
    availableForSale = available;
}

#include "SellableItem.h"

SellableItem::SellableItem(int i, QString n, float p, bool isAvailable) : id(i), name(n), price(p), availableForSale(isAvailable) {
}

SellableItem::SellableItem(QString n, float p) : name(n), price(p), availableForSale(false) {
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

float SellableItem::getPrice() {
    return price;
}

void SellableItem::setPrice(float newPrice) {
    price = newPrice;
}


bool SellableItem::getAvailability() {
    return availableForSale;
}

void SellableItem::setAvailability(bool available) {
    availableForSale = available;
}

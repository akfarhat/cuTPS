#include "SellableItem.h"

SellableItem::SellableItem(QString n, float p) : name(n), price(p), availableForSale(false) {

}

SellableItem::~SellableItem() {}

int SellableItem::getId() {
    return id;
}

QString SellableItem::getName() {
    return name;
}

float SellableItem::getPrice() {
    return price;
}


bool SellableItem::getAvailability() {
    return availableForSale;
}

void SellableItem::setAvailability(bool available) {
    availableForSale = available;
}

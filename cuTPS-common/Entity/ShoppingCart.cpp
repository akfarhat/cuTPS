#include "ShoppingCart.h"

ShoppingCart::ShoppingCart() {
    totalPrice = 0;
    items = new QVector<SellableItem*>();
}

ShoppingCart::~ShoppingCart() {
    delete items;
}

int ShoppingCart::getTotalPrice() {
    return totalPrice;
}

void ShoppingCart::addItem(SellableItem *newItem) {
    items->append(newItem);
    totalPrice += newItem->getPriceCents();
}

QVector<SellableItem*> ShoppingCart::getItems() {
    // Return a copy of the vector
    return QVector<SellableItem*>(*(this->items));
}

void ShoppingCart::clearCart() {
    items->clear();
    totalPrice = 0;
}

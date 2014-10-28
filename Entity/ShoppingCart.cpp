#include "ShoppingCart.h"

ShoppingCart::ShoppingCart() {
    totalPrice = 0;
    items = new QVector<SellableItem>();
}

ShoppingCart::~ShoppingCart() {
    delete items;
}

void ShoppingCart::addItem(SellableItem *newItem) {
    items->append(*newItem);
}

QVector<SellableItem> ShoppingCart::getItems() {
    // Return a copy of the vector
    return QVector<SellableItem>( *(this->items) );
}

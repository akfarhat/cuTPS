// Class: ShoppingCart
// Type: Entity
// Description:
//     Represents a list of items for sale in the system
//     that are ready to be ordered by a user for a
//     particular session

#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <QVector>
#include "SellableItem.h"

class ShoppingCart {
    private:
        // Members
        int totalPrice;
        QVector<SellableItem*> *items;

    public:
        // Methods
        ShoppingCart();
        ~ShoppingCart();
        int getTotalPrice();
        void addItem(SellableItem *);
        QVector<SellableItem*> getItems();

};

#endif // SHOPPINGCART_H

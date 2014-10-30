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

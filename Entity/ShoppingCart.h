#ifndef SHOPPINGCART_H
#define SHOPPINGCART_H

#include <QVector>
#include "SellableItem.h"

class ShoppingCart
{
    public:
        // Methods
        ShoppingCart();
        ~ShoppingCart();
        void addItem(SellableItem *);
        QVector<SellableItem> getItems();

    private:
        // Members
        int totalPrice;
        QVector<SellableItem> *items;
};

#endif // SHOPPINGCART_H

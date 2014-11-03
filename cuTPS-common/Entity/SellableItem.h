// Class: SellableItem
// Type: Entity
// Description:
//     Abstract class, representing the commonalities
//     of all items that the system has for sale


#ifndef SELLABLEITEM_H
#define SELLABLEITEM_H

#include<QString>

class SellableItem {

    private:
        int id;
        QString name;
        int priceCents;
        bool availableForSale;


    public:
        SellableItem();
        SellableItem(int, QString, int, bool);
        SellableItem(QString, int);
        ~SellableItem();
        int getId();
        void setId(int);
        QString getName();
        void setName(QString);
        int getPriceCents();
        void setPriceCents(int);
        bool getAvailability();
        void setAvailability(bool);

        virtual QString getType() = 0;
};

#endif // SELLABLEITEM_H

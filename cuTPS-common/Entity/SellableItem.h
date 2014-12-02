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

        void setId(const int);
        void setName(const QString);
        void setPriceCents(const int);
        void setAvailability(const bool);

        int getId() const;
        QString getName() const;
        int getPriceCents() const;
        bool getAvailability() const;

        // Return the formatted details for the item
        virtual QString getDetails() = 0;
        // Return the one-line list string
        virtual QString getTitle() = 0;
};

#endif // SELLABLEITEM_H

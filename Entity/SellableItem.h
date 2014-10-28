#ifndef SELLABLEITEM_H
#define SELLABLEITEM_H

#include<QString>

class SellableItem {

    private:
        int id;
        QString name;
        float price;
        bool availableForSale;


    public:
        SellableItem(QString, float);
        ~SellableItem();
        int getId();
        QString getName();
        float getPrice();
        bool getAvailability();

        void setAvailability(bool);

        virtual QString getType() = 0;
};

#endif // SELLABLEITEM_H

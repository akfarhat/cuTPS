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
        SellableItem();
        SellableItem(int, QString, float, bool);
        SellableItem(QString, float);
        ~SellableItem();
        int getId();
        void setId(int);
        QString getName();
        void setName(QString);
        float getPrice();
        void setPrice(float);
        bool getAvailability();
        void setAvailability(bool);

        virtual QString getType() = 0;
};

#endif // SELLABLEITEM_H

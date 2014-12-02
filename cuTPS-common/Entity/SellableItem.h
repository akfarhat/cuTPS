// Class: SellableItem
// Type: Entity
// Description:
//     Abstract class, representing the commonalities
//     of all items that the system has for sale


#ifndef SELLABLEITEM_H
#define SELLABLEITEM_H

#include <QString>
#include <QDataStream>

class SellableItem
{
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

    virtual QString getDetails() const = 0;

    // Serialization routines
    friend QDataStream& operator<< (QDataStream& os, const SellableItem& i); // output
    friend QDataStream& operator>> (QDataStream& is, SellableItem& i); // input

protected:
    int id;
    QString name;
    int priceCents;
    bool availableForSale;
};

#endif // SELLABLEITEM_H

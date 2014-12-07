// Class: SellableItem
// Type: Entity
// Description:
//     Abstract class, representing the commonalities
//     of all items that the system has for sale


#ifndef SELLABLEITEM_H
#define SELLABLEITEM_H

#include "libcutps_global.h"

#include <QString>
#include <QDataStream>

class LIBCUTPS_EXPORT SellableItem
{
public:
    SellableItem();

    SellableItem(qint32 id,
                 QString name,
                 quint32 price,
                 bool available=false);

    SellableItem(QString name,
                 quint32 price,
                 bool available=false);

    ~SellableItem();

    void setId(const qint32);
    void setName(const QString);
    void setPriceCents(const quint32);
    void setAvailability(const bool);

    qint32 getId() const;
    QString getName() const;
    quint32 getPriceCents() const;
    bool getAvailability() const;

    // Return the formatted details for the item
    virtual QString getDetails() const = 0;

    // Return the one-line list string
    virtual QString getTitle() = 0;
    virtual QString getType() = 0;
    
    // Serialization routines
    friend QDataStream& operator<< (QDataStream& os, const SellableItem& i); // output
    friend QDataStream& operator>> (QDataStream& is, SellableItem& i); // input

protected:
    qint32 id;
    QString name;
    quint32 priceCents;
    bool availableForSale;
};

#endif // SELLABLEITEM_H

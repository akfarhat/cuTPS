// Class: Textbook
// Type: Entity
// Description:
//     Entity object representing a textbook that
//     the system has available for purchase


#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include "SellableItem.h"
#include <QString>

class Textbook: public SellableItem {
    private:
        QString ISBN;
    public:
        Textbook();
        Textbook(int, QString, int, bool);
        Textbook(QString, int);
        ~Textbook();

        QString getISBN() const;
        void setISBN(const QString);

        QString getDetails();
};

#endif // TEXTBOOK_H

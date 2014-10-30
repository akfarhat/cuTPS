#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include "SellableItem.h"
#include <QString>

class Textbook: public SellableItem {
    private:
        QString ISBN;
    public:
        Textbook(int, QString, float);
        Textbook(QString, float);
        ~Textbook();
        QString getISBN();
        void setISBN(QString);

        QString getType();

};

#endif // TEXTBOOK_H

#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include "SellableItem.h"
#include <QString>

class Textbook: public SellableItem {
    private:
        int id;
        QString ISBN;
    public:
        Textbook();
        Textbook(int, QString, float, bool);
        Textbook(QString, float);
        ~Textbook();

        QString getISBN();
        void setISBN(QString);

        QString getType();

        int getTextbookId() const;
        void setTextbookId(int value);
};

#endif // TEXTBOOK_H

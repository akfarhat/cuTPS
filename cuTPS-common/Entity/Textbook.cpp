#include "Textbook.h"

Textbook::Textbook(int textId, QString name, float price, bool isAvailable, QString iISBN) : SellableItem(textId, name, price, isAvailable) {
    ISBN = iISBN;
}

Textbook::Textbook(QString name, float price) : SellableItem(name, price) {
}

Textbook::~Textbook() {
}


QString Textbook::getType() {
    return "Textbook";
}

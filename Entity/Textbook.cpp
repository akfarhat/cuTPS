#include "Textbook.h"

Textbook::Textbook(int textId, QString name, float price, bool isAvailable) : SellableItem(textId, name, price, isAvailable) {
}

Textbook::Textbook(QString name, float price) : SellableItem(name, price) {
}

Textbook::~Textbook() {
}


QString Textbook::getType() {
    return "Textbook";
}

#include "Textbook.h"

Textbook::Textbook(int textId, QString name, float price) : id(textId), SellableItem(name, price) {
}

Textbook::Textbook(QString name, float price) : SellableItem(name, price) {
}

Textbook::~Textbook() {
}


QString Textbook::getType() {
    return "Textbook";
}

#include "Textbook.h"

Textbook::Textbook(int textId, QString name, int price, bool isAvailable, QString iISBN) : SellableItem(textId, name, price, isAvailable) {
    ISBN = iISBN;
}

Textbook::Textbook(QString name, int price) : SellableItem(name, price) {
}

Textbook::Textbook() : SellableItem() {
    ISBN = ""; // This constructor invocation means this book is invalid
}

Textbook::~Textbook() {
}

QString Textbook::getISBN() const {
    return ISBN;
}

void Textbook::setISBN(const QString newISBN) {
    ISBN = newISBN;
}

QString Textbook::getDetails() {
    QString details = "";
    details += "Type: Textbook\n ID: ";
    details += QString::number(this->getId());
    details += "\nName: ";
    details += this->getName();
    details += "\nISBN: ";
    details += this->getISBN();
    details += "\nPrice: $";
    details += QString::number(this->getPriceCents() / 100.00f);
    details += "\nAvailable: ";
    details += (this->getAvailability() == true) ? "yes" : "no";
    return details;
}

QString Textbook::getTitle() {
    return this->getName() + " - " + this->getISBN();
}

QString Textbook::getType() {
    return "Textbook";
}

#include "Textbook.h"

Textbook::Textbook(int textId, QString name, int price, bool isAvailable, QString iISBN) : SellableItem(textId, name, price, isAvailable) {
    ISBN = iISBN;
}

Textbook::Textbook(QString name, int price) : SellableItem(name, price) {
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
    details += "\nPrice (in cents): ";
    details += QString::number(this->getPriceCents());
    details += "\nAvailable: ";
    details += (this->getAvailability() == true) ? "yes" : "no";
    return details;
}

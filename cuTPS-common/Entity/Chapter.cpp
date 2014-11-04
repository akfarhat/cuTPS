#include "Chapter.h"

Chapter::Chapter(int id, Textbook* textbook, int chNumber, QString name, int price, bool isAvailable) : SellableItem(id, name, price, isAvailable), parentTextbook(textbook), number(chNumber) {
}

Chapter::Chapter(Textbook* textbook, int chNumber, QString name, int price) :  SellableItem(name, price), parentTextbook(textbook), number(chNumber) {
}

Chapter::~Chapter() {
}

Textbook* Chapter::getParentTextbook() {
    return parentTextbook;
}

void Chapter::setParentTextbook(Textbook *newTextbook) {
    parentTextbook = newTextbook;
}

int Chapter::getChapterNumber() {
    return number;
}

void Chapter::setChapterNumber(int newNumber) {
    number = newNumber;
}

QString Chapter::getDetails() {
    QString details = "";
    details += "Type: Chapter\nID: ";
    details += QString::number(this->getId());
    details += "\nChapter Name: ";
    details += this->getName();
    details += "\nChapter Number: ";
    details += QString::number(this->getChapterNumber());
    details += "\nTextbook Name: ";
    details += this->getParentTextbook()->getName();
    details += "\nPrice (in cents): ";
    details += QString::number(this->getPriceCents());
    details += "\nAvailable: ";
    details += (this->getAvailability() == true) ? "yes" : "no";
    return details;
}

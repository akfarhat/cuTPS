#include "Section.h"

Section::Section(int id, Chapter* chapter, int num, QString name, int price, bool isAvailable) : SellableItem(id, name, price, isAvailable), parentChapter(chapter), number(num) {
}

Section::Section(Chapter* chapter, int num, QString name, int price) : SellableItem(name, price), parentChapter(chapter), number(num) {
}

Section::~Section() {
}

Chapter* Section::getParentChapter() {
    return parentChapter;
}

void Section::setParentChapter(Chapter* newChapter) {
    parentChapter = newChapter;
}

int Section::getSectionNumber() {
    return number;
}

void Section::setSectionNumber(int newNumber) {
    number = newNumber;
}

QString Section::getDetails() {
    QString details = "";
    details += "Type: Section\nID:";
    details += QString::number(this->getId());
    details += "\nSection Name: ";
    details += this->getName();
    details += "\nSection Number: ";
    details += QString::number(this->getSectionNumber());
    details += "\nChapter Name: ";
    details += this->getParentChapter()->getName();
    details += "\nChapter Number: ";
    details += QString::number(this->getParentChapter()->getChapterNumber());
    details += "\nTextbook Name: ";
    details += this->getParentChapter()->getParentTextbook()->getName();
    details += "\nPrice (in cents): ";
    details += QString::number(this->getPriceCents());
    details += "\nAvailable: ";
    details += (this->getAvailability() == true) ? "yes" : "no";
    return details;
}

#include "Chapter.h"

Chapter::Chapter(int id, Textbook* textbook, int chNumber, QString name, float price, bool isAvailable) : SellableItem(id, name, price, isAvailable), parentTextbook(textbook), number(chNumber) {
}

Chapter::Chapter(Textbook* textbook, int chNumber, QString name, float price) :  SellableItem(name, price), parentTextbook(textbook), number(chNumber) {
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

QString Chapter::getType() {
    return "Chapter";
}

int Chapter::getChapterId() const
{
    return id;
}

void Chapter::setChapterId(int value)
{
    id = value;
}

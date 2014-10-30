#include "Chapter.h"

Chapter::Chapter(int id, Textbook* textbook, int number, QString name, float price, bool isAvailable) : parentTextbook(textbook), chNumber(number), SellableItem(id, name, price, isAvailable) {
}

Chapter::Chapter(Textbook* textbook, int number, QString name, float price) : parentTextbook(textbook), chNumber(number), SellableItem(name, price) {
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

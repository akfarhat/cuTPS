#include "Chapter.h"

Chapter::Chapter(Textbook* textbook, int number, QString name, float price) : parentTextbook(textbook), chNumber(number), SellableItem(name, price) {

}

Chapter::~Chapter() {}

Textbook* Chapter::getParentTextbook() {
    return parentTextbook;
}

int Chapter::getChapterNumber() {
    return chNumber;
}

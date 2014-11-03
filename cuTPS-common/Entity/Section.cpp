#include "Section.h"

Section::Section(int id, Chapter* chapter, float num, QString name, float price, bool isAvailable) : SellableItem(id, name, price, isAvailable), parentChapter(chapter), number(num) {
}

Section::Section(Chapter* chapter, float num, QString name, float price) : SellableItem(name, price), parentChapter(chapter), number(num) {
}

Section::~Section() {
}

Chapter* Section::getParentChapter() {
    return parentChapter;
}

void Section::setParentChapter(Chapter* newChapter) {
    parentChapter = newChapter;
}

float Section::getSectionNumber() {
    return number;
}

void Section::setSectionNumber(float newNumber) {
    number = newNumber;
}

QString Section::getType() {
    return "Section";
}

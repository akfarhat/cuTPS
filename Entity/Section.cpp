#include "Section.h"

Section::Section(Chapter* chapter, int number, QString name, float price) : parentChapter(chapter), sectionNumber(number), SellableItem(name, price) {
}

Section::~Section() {}

Chapter* Section::getParentChapter() {
    return parentChapter;
}

int Section::getSectionNumber() {
    return sectionNumber;
}

QString Section::getType() {
    return "Section";
}

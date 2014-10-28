#ifndef SECTION_H
#define SECTION_H

#include "Chapter.h"
#include <QString>

class Section: public SellableItem {
    private:
        Chapter* parentChapter;
        int sectionNumber;

    public:
        Section(Chapter*, int, QString, float);
        ~Section();
        Chapter* getParentChapter();
        int getSectionNumber();

        QString getType();
};

#endif // SECTION_H

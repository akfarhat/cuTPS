#ifndef SECTION_H
#define SECTION_H

#include "Chapter.h"
#include <QString>

class Section: public SellableItem {
    private:
        Chapter* parentChapter;
        float number;

    public:
        Section(int, Chapter*, int, QString, float, bool);
        Section(Chapter*, int, QString, float);
        ~Section();

        Chapter* getParentChapter();
        void setParentChapter(Chapter*);

        float getSectionNumber();
        void setSectionNumber(float);

        QString getType();
};

#endif // SECTION_H

// Class: Section
// Type: Entity
// Description:
//     Entity object representing a section that
//     the system has available for purchase


#ifndef SECTION_H
#define SECTION_H

#include "Chapter.h"
#include <QString>

class Section: public SellableItem {
    private:
        Chapter* parentChapter;
        float number;

    public:
        Section();
        Section(int, Chapter*, float, QString, int, bool);
        Section(Chapter*, float, QString, int);
        ~Section();

        Chapter* getParentChapter();
        void setParentChapter(Chapter*);

        float getSectionNumber();
        void setSectionNumber(float);

        QString getDetails();
};

#endif // SECTION_H

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
        int number;

    public:
        Section();
        Section(int, Chapter*, int, QString, int, bool);
        Section(Chapter*, int, QString, int);
        ~Section();

        Chapter* getParentChapter();
        void setParentChapter(Chapter*);

        int getSectionNumber();
        void setSectionNumber(int);

        QString getDetails();
};

#endif // SECTION_H

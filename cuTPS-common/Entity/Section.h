// Class: Section
// Type: Entity
// Description:
//     Entity object representing a section that
//     the system has available for purchase

#ifndef SECTION_H
#define SECTION_H

#include "libcutps_global.h"

#include "SellableItem.h"
#include "Chapter.h"

#include <QString>
#include <QDataStream>

class LIBCUTPS_EXPORT Section : public SellableItem
{
public:
    Section();
    Section(int, Chapter*, int, QString, int, bool);
    Section(Chapter*, int, QString, int);
    virtual ~Section();

    Chapter* getParentChapter();
    void setParentChapter(Chapter*);

    int getSectionNumber() const;
    void setSectionNumber(int);

    QString getDetails() const;

    friend QDataStream& operator<<(QDataStream& os, const Section& s); // output
    friend QDataStream& operator>>(QDataStream& is, Section& s); // input

private:
    Chapter* parentChapter;
    int number;
    int parentChapterId;
};

#endif // SECTION_H

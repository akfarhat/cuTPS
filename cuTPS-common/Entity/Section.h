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

    Section(qint32 id,
            Chapter* parent,
            quint16 number,
            QString title,
            quint32 price,
            bool available=false);

    Section(Chapter* parent,
            quint16 number,
            QString name,
            quint32 price,
            bool available=false);

    virtual ~Section();

    Chapter* getParentChapter();
    void setParentChapter(Chapter*);

    quint16 getSectionNumber() const;
    void setSectionNumber(quint16);

    qint32 getParentChapterId() const;
    void setParentChapterId(const qint32 value);

    qint32 getParentTextbookId() const;
    void setParentTextbookId(const qint32 value);

    QString getDetails() const;
    QString getTitle();
    QString getType();

    friend QDataStream& operator<<(QDataStream& os, const Section& s); // output
    friend QDataStream& operator>>(QDataStream& is, Section& s); // input


private:
    Chapter* parentChapter;
    quint16 number;
    qint32 parentChapterId;
    qint32 parentTextbookId;
};

#endif // SECTION_H

// Class: Chapter
// Type: Entity
// Description:
//     Entity object representing a chapter that
//     the system has available for purchase


#ifndef CHAPTER_H
#define CHAPTER_H

#include "libcutps_global.h"

#include "SellableItem.h"
#include "Textbook.h"

#include <QString>
#include <QDataStream>
#include <QVector>

class Section;

class LIBCUTPS_EXPORT Chapter: public SellableItem
{
public:
    Chapter();

    Chapter(Chapter&); // Copy cTor

    Chapter(qint32 id,
            Textbook* parent,
            quint16 number,
            QString title,
            quint32 price,
            bool available);

    Chapter(Textbook* parent,
            quint16 number,
            QString title,
            quint32 price,
            bool available);

    virtual ~Chapter();

    Textbook* getParentTextbook();
    void setParentTextbook(Textbook*);

    quint16 getChapterNumber() const;
    void setChapterNumber(quint16);

    qint32 getParentTextbookId() const;
    void setParentTextbookId(const qint32 value);

    void addSection(const Section& s);
    QVector<Section*>& getSectionList();
    int numSections() const;
    
    QString getTitle();
    QString getType();
    QString getDetails() const;

    friend QDataStream& operator<<(QDataStream& os, const Chapter& c); // output
    friend QDataStream& operator>>(QDataStream& is, Chapter& c); // input

private:
    Textbook* parentTextbook;
    quint16 number;
    qint32 parentTextbookId;
    QVector<Section*> sections;
};

#endif // CHAPTER_H

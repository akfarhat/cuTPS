// Class: Chapter
// Type: Entity
// Description:
//     Entity object representing a chapter that
//     the system has available for purchase


#ifndef CHAPTER_H
#define CHAPTER_H

#include "SellableItem.h"
#include "Textbook.h"

#include <QString>
#include <QDataStream>
#include <QVector>

class Section;

class Chapter: public SellableItem
{
public:
    Chapter();
    Chapter(Chapter&); // Copy cTor
    Chapter(int, Textbook*, int, QString, int, bool);
    Chapter(Textbook*, int, QString, int);
    virtual ~Chapter();

    Textbook* getParentTextbook();
    void setParentTextbook(Textbook*);

    int getChapterNumber() const;
    void setChapterNumber(int);

    void addSection(const Section& s);
    QVector<Section*> getSectionList();
    int numSections() const;

    QString getDetails() const;

    friend QDataStream& operator<<(QDataStream& os, const Chapter& c); // output
    friend QDataStream& operator>>(QDataStream& is, Chapter& c); // input

private:
    Textbook* parentTextbook;
    int number;
    int parentTextbookId;
    QVector<Section*> sections;
};

#endif // CHAPTER_H

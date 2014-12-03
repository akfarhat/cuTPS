// Class: Textbook
// Type: Entity
// Description:
//     Entity object representing a textbook that
//     the system has available for purchase


#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include "SellableItem.h"

#include <QString>
#include <QDataStream>
#include <QVector>

class Chapter;

class Textbook : public SellableItem {
public:
    Textbook();
    Textbook(const Textbook&); // Copy cTor
    Textbook(int, QString, int, bool, QString);
    Textbook(QString, int);
    virtual ~Textbook();

    QString getISBN() const;
    void setISBN(const QString);

    QString getDetails() const;

    void addChapter(const Chapter& c);
    QVector<Chapter*> getChapterList();
    const QVector<Chapter*> getConstChapterList() const;
    int numChapters() const;

    // Serialization routines
    friend QDataStream& operator<<(QDataStream& os, const Textbook& b); // output
    friend QDataStream& operator>>(QDataStream& is, Textbook& b); // input

private:
    QString ISBN;
    QVector<Chapter*> chapters;
};

#endif // TEXTBOOK_H

// Class: Textbook
// Type: Entity
// Description:
//     Entity object representing a textbook that
//     the system has available for purchase


#ifndef TEXTBOOK_H
#define TEXTBOOK_H

#include "libcutps_global.h"

#include "SellableItem.h"

#include <QString>
#include <QDataStream>
#include <QVector>

class Chapter;

class LIBCUTPS_EXPORT Textbook : public SellableItem {
public:
    Textbook();
    Textbook(const Textbook&); // Copy cTor
    Textbook(int id,
             QString name,
             QString edition,
             QString authors,
             int price,
             bool avail,
             QString isbn);
    Textbook(QString, int);
    virtual ~Textbook();

    QString getISBN() const;
    void setISBN(const QString&);
    QString getAuthors() const;
    void setAuthors(const QString &value);
    QString getEdition() const;
    void setEdition(const QString &value);

    QString getDetails() const;
    QString getTitle();
    QString getType();

    void addChapter(const Chapter& c);
    QVector<Chapter*>& getChapterList();
    const QVector<Chapter*> getConstChapterList() const;
    int numChapters() const;

    // Serialization routines
    friend QDataStream& operator<<(QDataStream& os, const Textbook& b); // output
    friend QDataStream& operator>>(QDataStream& is, Textbook& b); // input

private:
    QString authors;
    QString isbn;
    QString edition;
    QVector<Chapter*> chapters;
};

#endif // TEXTBOOK_H

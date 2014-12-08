#include "Textbook.h"
#include "Chapter.h"
#include "SellableItem.h"
#include "Defines.h"

Textbook::Textbook(int textId, QString name, int price, bool isAvailable, QString iISBN) : SellableItem(textId, name, price, isAvailable) {
    ISBN = iISBN;
}

Textbook::Textbook(const Textbook& src) : SellableItem(src.getId(), src.getName(), src.getPriceCents(), src.getAvailability()), ISBN(src.getISBN())
{
    // Copy over all the chapters
    for (Chapter* c : src.getConstChapterList())
    {
        addChapter(*c);
    }
}

Textbook::Textbook(QString name, int price) : SellableItem(name, price) {
}

Textbook::Textbook() : SellableItem() {
    ISBN = ""; // This constructor invocation means this book is invalid
}

Textbook::~Textbook() {
    for (Chapter* c : chapters)
        delete c;
}

QString Textbook::getISBN() const {
    return ISBN;
}

void Textbook::setISBN(const QString newISBN) {
    ISBN = newISBN;
}

QString Textbook::getDetails() const {
    return QString("[Textbook: ID=%1, Title='%2', ISBN=%3, $$=%4, OnSell? %5]")
            .arg(QString::number(getId()),
                 getName(),
                 getISBN(),
                 QString::number(this->getPriceCents() / 100.00f),
                 (getAvailability() ? "yes" : "no"));
}

void Textbook::addChapter(const Chapter& c)
{
    Chapter* c_copy = new Chapter(const_cast<Chapter&>(c));
    c_copy->setParentTextbook(this);
    chapters.append(c_copy);
}

QVector<Chapter*> Textbook::getChapterList()
{
    return chapters;
}

const QVector<Chapter*> Textbook::getConstChapterList() const
{
    return chapters;
}

int Textbook::numChapters() const
{
    return chapters.size();
}

QString Textbook::getTitle() {
    return this->getName() + " - " + this->getISBN();
}

QString Textbook::getType() {
    return "Textbook";
}

QDataStream& operator<<(QDataStream& os, const Textbook& b)
{
    os.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

    // Insert Textbook itself
    os << dynamic_cast<const SellableItem&>(b);
    os << b.ISBN;

    // Followed by number of chapters
    os << static_cast<qint32>(b.numChapters());

    // Followed by every chapter (sections included)
    for (Chapter* c : b.chapters) {
        os << *c;
    }

    return os;
}

QDataStream& operator>>(QDataStream& is, Textbook& b)
{
    is.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

    // Read textbook
    is >> dynamic_cast<SellableItem&>(b);
    is >> b.ISBN;

    // Read number of chapters
    qint32 numChapters;
    is >> numChapters;

    // Read all the chapters
    for (int i = 0; i < numChapters; ++i) {
        Chapter c;
        is >> c;
        b.addChapter(c);
    }

    return is;
}

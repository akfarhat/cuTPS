#include "Textbook.h"
#include "Chapter.h"
#include "SellableItem.h"
#include "Defines.h"

Textbook::Textbook(int textId, QString name, QString edition, QString authors, int price, bool isAvailable, QString iISBN)
    : SellableItem(textId, name, price, isAvailable),
    authors(authors), isbn(iISBN), edition(edition)
{
}

Textbook::Textbook(int textId, QString edition, QString authors, QString iISBN, QString name, int price, bool isAvailable)
    : SellableItem(textId, name, price, isAvailable),
    authors(authors), isbn(iISBN), edition(edition)
{
}

Textbook::Textbook(const Textbook& src)
    : SellableItem(src.getId(), src.getName(), src.getPriceCents(), src.getAvailability()),
      isbn(src.getISBN()), authors(src.getAuthors()), edition(src.getEdition())
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
    isbn = ""; // This constructor invocation means this book is invalid
}

Textbook::~Textbook() {
    for (Chapter* c : chapters)
        if (c != NULL) delete c;
}

QString Textbook::getISBN() const {
    return isbn;
}

void Textbook::setISBN(const QString& newISBN) {
    isbn = newISBN;
}

QString Textbook::getDetails() const {
    return QString("Item ID: %1,\nName: '%2'\nAuthors: %6\nEdition: %7\nISBN: %3\nPrice: $%4\nAvailable for Sale: %5")
            .arg(QString::number(getId()),
                 getName(),
                 getISBN(),
                 QString::number(this->getPriceCents() / 100.00f),
                 (getAvailability() ? "yes" : "no"),
                 getAuthors(),
                 getEdition());
}

void Textbook::addChapter(const Chapter& c)
{
    Chapter* c_copy = new Chapter(const_cast<Chapter&>(c));
    c_copy->setParentTextbook(this);
    chapters.append(c_copy);
}

QVector<Chapter*>& Textbook::getChapterList()
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

QString Textbook::getEdition() const
{
    return edition;
}

void Textbook::setEdition(const QString &value)
{
    edition = value;
}

QString Textbook::getAuthors() const
{
    return authors;
}

void Textbook::setAuthors(const QString &value)
{
    authors = value;
}

QString Textbook::getTitle() {
    return this->getName() + " - " + this->getISBN();
}

QString Textbook::getType() {
    return "Textbook";
}

QDataStream& operator<<(QDataStream& os, const Textbook& b)
{
    os.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    // Insert Textbook itself
    os << dynamic_cast<const SellableItem&>(b);
    os << b.edition;
    os << b.authors;
    os << b.isbn;

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
    is.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    // Read textbook
    is >> dynamic_cast<SellableItem&>(b);
    is >> b.edition;
    is >> b.authors;
    is >> b.isbn;

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

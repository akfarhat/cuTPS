#include "Chapter.h"
#include "Section.h"
#include "Defines.h"

Chapter::Chapter()
{
    number = 1;
}

Chapter::Chapter(Chapter& src)
    : SellableItem(src.getId(),
                   src.getName(),
                   src.getPriceCents(),
                   src.getAvailability()),
      parentTextbook(src.getParentTextbook()),
      number(src.getChapterNumber())
{
    for (Section* s : src.getSectionList())
    {
        this->addSection(*s);
    }
}

Chapter::Chapter(qint32 id,
                 Textbook* textbook,
                 quint16 chNumber,
                 QString name,
                 quint32 price,
                 bool available)
    : SellableItem(id, name, price, available),
      parentTextbook(textbook), number(chNumber)
{
}

Chapter::Chapter(Textbook* textbook,
                 quint16 chNumber,
                 QString name,
                 quint32 price,
                 bool available)
    :  SellableItem(name, price, available),
      parentTextbook(textbook), number(chNumber)
{
}

Chapter::~Chapter() {
    for (Section* s : sections)
        if (s != NULL) delete s;
}

Textbook* Chapter::getParentTextbook() {
    return parentTextbook;
}

void Chapter::setParentTextbook(Textbook *newTextbook) {
    parentTextbook = newTextbook;
    parentTextbookId = newTextbook->getId();
}

quint16 Chapter::getChapterNumber() const {
    return number;
}

void Chapter::setChapterNumber(quint16 newNumber) {
    number = newNumber;
}

QString Chapter::getDetails() const {
    QString bookName = parentTextbook == NULL
            ? "NULL" : parentTextbook->getName();
    QString details = "";
    details += "Item ID: ";
    details += QString::number(this->getId());
    details += "\nChapter Name: ";
    details += this->getName();
    details += "\nChapter Number: ";
    details += QString::number(this->getChapterNumber());
    details += "\nTextbook Name: ";
    details += bookName;
    details += "\nPrice: $";
    details += QString::number(this->getPriceCents() / 100.00f);
    details += "\nAvailable for Sale: ";
    details += (this->getAvailability() == true) ? "yes" : "no";
    return details;
}

qint32 Chapter::getParentTextbookId() const
{
    return parentTextbookId;
}

void Chapter::setParentTextbookId(const qint32 value)
{
    parentTextbookId = value;
}

void Chapter::addSection(const Section& s)
{
    Section* s_copy = new Section(s);
    s_copy->setParentChapter(this);
    sections.append(s_copy);
}

QString Chapter::getTitle() {
    return "Chapter " + QString::number(this->getChapterNumber()) + ": " + this->getName();
}

QString Chapter::getType() {
    return "Chapter";
}

QVector<Section*>& Chapter::getSectionList()
{
    return sections;
}

quint16 Chapter::numSections() const
{
    return sections.size();
}

QDataStream& operator<<(QDataStream& os, const Chapter& c)
{
    os.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    // Insert chapter
    os << dynamic_cast<const SellableItem&>(c);
    os << c.number; // quint16
    os << c.parentTextbookId; // qint32

    // Followed by number of sections
    os << c.numSections(); // quint16

    // And every section
    for (Section* s : c.sections) {
        os << *s;
    }

    return os;
}

QDataStream& operator>>(QDataStream& is, Chapter& c)
{
    is.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    // Read chapter
    is >> dynamic_cast<SellableItem&>(c);
    is >> c.number;
    is >> c.parentTextbookId;

    // Read number of sections
    quint16 numSections;
    is >> numSections;

    // Read sections
    for (int i = 0; i < numSections; ++i) {
        Section s;
        is >> s;
        s.setParentChapter(&c);
        c.addSection(s);
    }

    return is;
}

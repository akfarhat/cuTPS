#include "Chapter.h"
#include "Section.h"
#include "Defines.h"

Chapter::Chapter() {}

Chapter::Chapter(Chapter& src)
    : SellableItem(src.getId(), src.getName(), src.getPriceCents(), src.getAvailability()),
      parentTextbook(src.getParentTextbook()),
      number(src.getChapterNumber())
{
    for (Section* s : src.getSectionList())
    {
        this->addSection(*s);
    }
}

Chapter::Chapter(int id, Textbook* textbook, int chNumber, QString name, int price, bool isAvailable) : SellableItem(id, name, price, isAvailable), parentTextbook(textbook), number(chNumber) {
}

Chapter::Chapter(Textbook* textbook, int chNumber, QString name, int price) :  SellableItem(name, price), parentTextbook(textbook), number(chNumber) {
}

Chapter::~Chapter() {
    for (Section* s : sections)
        delete s;
}

Textbook* Chapter::getParentTextbook() {
    return parentTextbook;
}

void Chapter::setParentTextbook(Textbook *newTextbook) {
    parentTextbook = newTextbook;
    parentTextbookId = newTextbook->getId();
}

int Chapter::getChapterNumber() const {
    return number;
}

void Chapter::setChapterNumber(int newNumber) {
    number = newNumber;
}

QString Chapter::getDetails() const {
    QString details = "";
    details += "Type: Chapter\nID: ";
    details += QString::number(this->getId());
    details += "\nChapter Name: ";
    details += this->getName();
    details += "\nChapter Number: ";
    details += QString::number(this->getChapterNumber());
//    details += "\nTextbook Name: ";
//    details += this->getParentTextbook()->getName();
    details += "\nPrice (in cents): ";
    details += QString::number(this->getPriceCents());
    details += "\nAvailable: ";
    details += (this->getAvailability() == true) ? "yes" : "no";
    return details;
}

void Chapter::addSection(const Section& s)
{
    Section* s_copy = new Section(s);
    s_copy->setParentChapter(this);
    sections.append(s_copy);
}

QVector<Section*> Chapter::getSectionList()
{
    return sections;
}

int Chapter::numSections() const
{
    return sections.size();
}

QDataStream& operator<<(QDataStream& os, const Chapter& c)
{
    os.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

    // Insert chapter
    os << dynamic_cast<const SellableItem&>(c);
    os << static_cast<qint32>(c.number);
    os << static_cast<qint32>(c.parentTextbookId);
    // Followed by number of sections
    os << static_cast<qint32>(c.numSections());
    // And every section
    for (Section* s : c.sections) {
        os << *s;
    }

    return os;
}

QDataStream& operator>>(QDataStream& is, Chapter& c)
{
    is.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

    // Read chapter
    is >> dynamic_cast<SellableItem&>(c);
    qint32 parentId, chNumber, numSections;
    is >> chNumber >> parentId;
    c.parentTextbookId = parentId;
    c.number = chNumber;

    // Read number of sections
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

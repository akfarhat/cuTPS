#include "Section.h"
#include "Defines.h"

Section::Section() {}

Section::Section(qint32 id,
                 Chapter* chapter,
                 quint16 num,
                 QString name,
                 quint32 price,
                 bool isAvailable)
    : SellableItem(id, name, price, isAvailable),
      parentChapter(chapter), number(num)
{
}

Section::Section(Chapter* chapter,
                 quint16 num,
                 QString name,
                 quint32 price,
                 bool available)
    : SellableItem(name, price, available),
      parentChapter(chapter), number(num)
{
}

Section::~Section()
{
}

Chapter* Section::getParentChapter() {
    return parentChapter;
}

void Section::setParentChapter(Chapter* newChapter) {
    parentChapter = newChapter;
    parentChapterId = newChapter->getId();
}

quint16 Section::getSectionNumber() const {
    return number;
}

void Section::setSectionNumber(quint16 newNumber) {
    number = newNumber;
}

QString Section::getDetails() const {
    QString textbookName = "NULL";
    QString chapterName = "NULL";
    QString chapterNum = "NULL";
    if (parentChapter != NULL) {
        chapterName = parentChapter->getName();
        chapterNum = QString::number(parentChapter->getChapterNumber());
        if (parentChapter->getParentTextbook() != NULL)
            textbookName = parentChapter->getParentTextbook()->getName();
    }

    QString details = "";
    details += "Type: Section\nID:";
    details += QString::number(this->getId());
    details += "\nSection Name: ";
    details += this->getName();
    details += "\nSection Number: ";
    details += QString::number(this->getSectionNumber());
    details += "\nChapter Name: ";
    details += chapterName;
    details += "\nChapter Number: ";
    details += chapterNum;
    details += "\nTextbook Name: ";
    details += textbookName;
    details += "\nPrice: $";
    details += QString::number(this->getPriceCents() / 100.00f);
    details += "\nAvailable: ";
    details += (this->getAvailability() == true) ? "yes" : "no";
    return details;
}

QString Section::getTitle() {
    return "Section " + QString::number(this->getSectionNumber())
                      + ": " + this->getName();
}

QString Section::getType() {
    return "Section";
}
qint32 Section::getParentChapterId() const
{
    return parentChapterId;
}

void Section::setParentChapterId(const qint32 value)
{
    parentChapterId = value;
}

qint32 Section::getParentTextbookId() const
{
    return parentTextbookId;
}

void Section::setParentTextbookId(const qint32 value)
{
    parentTextbookId = value;
}

QDataStream& operator<<(QDataStream& os, const Section& s)
{
    os.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    os << dynamic_cast<const SellableItem&>(s);
    os << s.number; // quint32
    os << s.parentChapterId; // qint32

    return os;
}

QDataStream& operator>>(QDataStream& is, Section& s)
{
    is.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    is >> dynamic_cast<SellableItem&>(s);
    is >> s.number;
    is >> s.parentChapterId;

    return is;
}

#include "Section.h"
#include "Defines.h"

Section::Section() {}

Section::Section(int id, Chapter* chapter, int num, QString name, int price, bool isAvailable) : SellableItem(id, name, price, isAvailable), parentChapter(chapter), number(num) {
}

Section::Section(Chapter* chapter, int num, QString name, int price) : SellableItem(name, price), parentChapter(chapter), number(num) {
}

Section::~Section() {
}

Chapter* Section::getParentChapter() {
    return parentChapter;
}

void Section::setParentChapter(Chapter* newChapter) {
    parentChapter = newChapter;
    parentChapterId = newChapter->getId();
}

int Section::getSectionNumber() const {
    return number;
}

void Section::setSectionNumber(int newNumber) {
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

QDataStream& operator<<(QDataStream& os, const Section& s)
{
    os.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

    os << dynamic_cast<const SellableItem&>(s);
    os << static_cast<qint32>(s.number);
    os << static_cast<qint32>(s.parentChapterId);

    return os;
}

QDataStream& operator>>(QDataStream& is, Section& s)
{
    is.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

    is >> dynamic_cast<SellableItem&>(s);
    qint32 parentId, sNumber;
    is >> sNumber >> parentId;
    s.parentChapterId = parentId;
    s.number = sNumber;

    return is;
}

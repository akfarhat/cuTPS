#include "Course.h"
#include "Defines.h"

Course::Course() {
    code = "";
    requiredBooks = new QVector<Textbook*>();
}

Course::Course(QString course) {
    code = course;
    name = "";
    requiredBooks = new QVector<Textbook*>();
}

Course::Course(QString course, QString courseName, QVector<Textbook*> books) {
    code = course;
    name = courseName;
    requiredBooks = new QVector<Textbook*>();

    for (int i=0; i<books.size(); i++) {
        requiredBooks->append(books[i]);
    }
}

Course::~Course() {
    delete requiredBooks;
}

int Course::getId() const {
    return id;
}

void Course::setId(const int newId) {
    id = newId;
}

QString Course::getCourseCode() const {
    return code;
}

void Course::setCourseCode(const QString newCode) {
    code = newCode;
}

void Course::addRequiredText(Textbook *book) {
    requiredBooks->append(book);
}

QVector<Textbook*>* Course::getRequiredTexts() const {
    // Return a pointer to the vector contatining books
    return this->requiredBooks;
}

QVector<qint32>* Course::getRequiredTextsIds() const {
    return this->reqBooksIds;
}

QString Course::getCourseName() const
{
    return name;
}

void Course::setCourseName(const QString &value)
{
    name = value;
}

QString Course::stringRepr() const {
    return QString("[Course: %1: %2. (id=%3)]")
            .arg(getCourseCode(), getCourseName(), QString::number(getId()));
}

QDataStream& operator<<(QDataStream& os, const Course& c)
{
    os.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

    // Write course data
    os << static_cast<qint32>(c.id)
       << c.name
       << c.code;

    // Then required textbooks count..
    os << static_cast<quint16>(c.requiredBooks->size());

    // .. followed by this many textbook IDs
    for (Textbook* b : *(c.requiredBooks))
    {
        os << static_cast<qint32>(b->getId());
    }

    return os;
}

QDataStream& operator>>(QDataStream& is, Course& c)
{
    is.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

    qint32 courseId;
    quint16 textCount;
    QString name, code;

    is >> courseId
       >> name
       >> code;

    c.name = name;
    c.code = code;
    c.id = courseId;

    is >> textCount;

    c.reqBooksIds = new QVector<qint32>();
    qint32 id;

    for (int i = 0; i < textCount; ++i)
    {
        is >> id;
        c.reqBooksIds->append(id);
    }

    return is;
}

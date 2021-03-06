#include "Course.h"
#include "Defines.h"

Course::Course(qint32 cid, QString ccode, QString cname, QString csection, qint32 cyear)
    : id(cid), code(ccode), name(cname), termSection(csection), termYear(cyear)
{
}

Course::Course(const QString course,
               const QString courseName)
    : id(-1), code(course), name(courseName)
{
}

Course::~Course() {}

qint32 Course::getId() const
{
    return id;
}

void Course::setId(const qint32 newId)
{
    id = newId;
}

QString Course::getCourseCode() const
{
    return code;
}

void Course::setCourseCode(const QString newCode)
{
    code = newCode;
}

void Course::addRequiredTextId(qint32 id)
{
    reqBooksIds.append(id);
}

void Course::addRequiredTextIds(const QVector<qint32>& v)
{
    for (int i : v) addRequiredTextId(i);
}

const QVector<qint32>& Course::getRequiredTextIds() const
{
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

QString Course::getTermSection() const
{
    return termSection;
}

void Course::setTermSection(const QString value)
{
    // Take first uppercase letter
    termSection = value.toUpper().at(0);
}

qint32 Course::getTermYear() const
{
    return termYear;
}

void Course::setTermYear(const qint32 value)
{
    termYear = value;
}

QDataStream& operator<<(QDataStream& os, const Course& c)
{
    os.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    // Write course data
    os << c.id
       << c.name
       << c.code
       << c.termSection
       << c.termYear;

    // Then required textbooks count..
    os << static_cast<quint16>(c.reqBooksIds.size());

    // .. followed by this many textbook IDs
    for (qint32 id : c.reqBooksIds)
    {
        os << id;
    }

    return os;
}

QDataStream& operator>>(QDataStream& is, Course& c)
{
    is.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    is >> c.id
       >> c.name
       >> c.code
       >> c.termSection
       >> c.termYear;

    quint16 textCount;
    c.reqBooksIds.clear();

    is >> textCount;

    for (int i = 0; i < textCount; ++i)
    {
        qint32 id;
        is >> id;
        c.reqBooksIds.append(id);
    }

    return is;
}

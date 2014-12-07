#include "Course.h"
#include "Defines.h"

Course::Course(const QString course,
               const QString courseName)
{
    code = course;
    name = courseName;
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

QDataStream& operator<<(QDataStream& os, const Course& c)
{
    os.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    // Write course data
    os << c.id
       << c.name
       << c.code;

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
       >> c.code;

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

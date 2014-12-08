// Class: Course
// Type: Entity
// Description:
//     represents a course that the system offers content for


#ifndef COURSE_H
#define COURSE_H

#include "libcutps_global.h"

#include <QVector>
#include <QString>
#include <QDataStream>

#include "Textbook.h"

using namespace std;

class LIBCUTPS_EXPORT Course
{
public:
    Course(const QString ccode="UKWN0000", const QString cname="<NO_COURSE_NAME>");
    ~Course();

    qint32 getId() const;
    void setId(const qint32);

    QString getCourseCode() const;
    void setCourseCode(const QString);

    void addRequiredTextId(qint32 rtextId);
    void addRequiredTextIds(const QVector<qint32>& vec);
    const QVector<qint32>& getRequiredTextIds() const;

    QString getCourseName() const;
    void setCourseName(const QString &value);

    friend QDataStream& operator<<(QDataStream& os, const Course& c); // output
    friend QDataStream& operator>>(QDataStream& is, Course& c); // input

    QString stringRepr() const;

    QString getTermSection() const;
    void setTermSection(const QString value);

    qint32 getTermYear() const;
    void setTermYear(const qint32 value);

private:
    qint32  id;
    QString code;
    QString name;
    QString termSection;
    qint32  termYear;

    // Note. Whenever a Course object is sent over network, only IDs of required texts
    // will be actually sent (as reqBooksIds). This is for performance reasons.
    // I.e. freshly received course object from the server only knows how many texts
    // are required by this course + their IDs. To get actual Textbook by id, use
    // getBookDetails() API call.
    QVector<qint32> reqBooksIds;

};

#endif // COURSE_H

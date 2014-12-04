// Class: Course
// Type: Entity
// Description:
//     represents a course that the system offers content for


#ifndef COURSE_H
#define COURSE_H

#include <QVector>
#include <QString>
#include <QDataStream>

#include "Textbook.h"

using namespace std;

class Course
{
public:
    Course();
    Course(const QString ccode);
    Course(const QString ccode, const QString cname, const QVector<Textbook*>&);
    ~Course();

    int getId() const;
    void setId(const int);

    QString getCourseCode() const;
    void setCourseCode(const QString);

    void addRequiredText(Textbook*);
    QVector<Textbook*>* getRequiredTexts();
    QVector<qint32>* getRequiredTextsIds();

    QString getCourseName() const;
    void setCourseName(const QString &value);

    friend QDataStream& operator<<(QDataStream& os, const Course& c); // output
    friend QDataStream& operator>>(QDataStream& is, Course& c); // input

    QString stringRepr() const;

private:
    int id;
    QString code;
    QString name;

    // Note. Whenever a Course object is sent over network, only IDs of required texts
    // will be actually sent (as reqBooksIds). This is for performance reasons.
    // I.e. freshly received course object from the server only knows how many texts
    // are required by this course + their IDs. To get actual Textbook by id, use
    // getBookDetails() API call.
    QVector<Textbook*> requiredBooks; // TODO: make it legacy or remove?
    QVector<qint32> reqBooksIds;

};

#endif // COURSE_H

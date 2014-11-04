// Class: Course
// Type: Entity
// Description:
//     represents a course that the system offers content for


#ifndef COURSE_H
#define COURSE_H

#include <QVector>
#include <QString>
#include "Textbook.h"

using namespace std;

class Course {

    private:
        int id;
        QString code;
        QString name;
        QVector<Textbook*> *requiredBooks;

    public:
        Course(QString);
        Course(QString, QVector<Textbook*>);
        ~Course();

        int getId() const;
        void setId(const int);

        QString getCourseCode() const;
        void setCourseCode(const QString);

        void addRequiredText(Textbook *);
        QVector<Textbook*>* getRequiredTexts() const;

        QString getCourseName() const;
        void setCourseName(const QString &value);
};

#endif // COURSE_H

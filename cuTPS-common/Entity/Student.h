// Class: Student
// Type: Entity
// Description:
//     Represents the type of user that can browse
//     and order the content offered in the system for
//     courses that they are registed in.

#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "Course.h"
#include <QString>
#include <QVector>

using namespace std;

class Student: public User {

    private:
        int studentNumber;
        QString emailAddress;
        QVector<Course*> courses;


    public:
        Student(int, QString, QString, int);
        ~Student();

        int getStudentNumber();
        void setStudentNumber(int);

        QString getEmailAddress();
        void setEmailAddress(QString);

        QVector<Course*> getCourses();
        void enrollInCourse(Course*);

        QString getDetails();
};

#endif // STUDENT_H

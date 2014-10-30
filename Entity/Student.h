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
        QVector<Course> courses;


    public:
        Student(QString, QString);
        ~Student();

        int getStudentNumber();
        void setStudentNumber(int);

        QString getEmailAddress();
        void setEmailAddress(QString);

        QString getType();
};

#endif // STUDENT_H

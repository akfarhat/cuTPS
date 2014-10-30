#ifndef COURSE_H
#define COURSE_H

#include <QVector>
#include <QString>
#include "Textbook.h"

using namespace std;

class Course {

    private:
        QString code;
        QVector<Textbook> *requiredBooks;

    public:
        Course(QString);
        Course(QString, QVector<Textbook>);
        ~Course();

        QString getCourseCode();
        void setCourseCode(QString);

        void addRequiredText(Textbook *);
        QVector<Textbook> getRequiredTexts();


};

#endif // COURSE_H

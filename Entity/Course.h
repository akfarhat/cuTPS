#ifndef COURSE_H
#define COURSE_H

#include <QVector>
#include <QString>
#include "Textbook.h"

using namespace std;

class Course {

    public:
        Course(QString);
        Course(QString, QVector<Textbook>);
        ~Course();

        void addRequiredText(Textbook *);
        QVector<Textbook> getRequiredTexts();

    private:
        QString courseCode;
        QVector<Textbook> *requiredBooks;

};

#endif // COURSE_H

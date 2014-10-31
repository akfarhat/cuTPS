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
        QVector<Textbook*> *requiredBooks;

    public:
        Course(QString);
        Course(QString, QVector<Textbook*>);
        ~Course();

        int getCourseId();
        void setCourseId(int);

        QString getCourseCode();
        void setCourseCode(QString);

        void addRequiredText(Textbook *);
        QVector<Textbook*> getRequiredTexts();


};

#endif // COURSE_H

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

        int getId();
        void setId(int);

        QString getCourseCode();
        void setCourseCode(QString);

        void addRequiredText(Textbook *);
        QVector<Textbook*> getRequiredTexts();


        QString getCourseName() const;
        void setCourseName(const QString &value);
};

#endif // COURSE_H

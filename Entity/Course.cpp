#include "Course.h"

Course::Course(QString course) {
    courseCode = course;
    requiredBooks = new QVector<Textbook>();
}

Course::Course(QString course, QVector<Textbook> books) {
    courseCode = course;
    requiredBooks = new QVector<Textbook>();

    for (int i=0; i<books.size(); i++) {
        requiredBooks->append(books[i]);
    }
}

Course::~Course() {
    delete requiredBooks;
}

void Course::addRequiredText(Textbook *book) {
    requiredBooks->append(*book);
}

QVector<Textbook> Course::getRequiredTexts() {
    // Return a copy of the vector
    return QVector<Textbook>( *(this->requiredBooks) );
}

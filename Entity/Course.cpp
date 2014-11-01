#include "Course.h"

Course::Course(QString course) {
    code = course;
    requiredBooks = new QVector<Textbook*>();
}

Course::Course(QString course, QVector<Textbook*> books) {
    code = course;
    requiredBooks = new QVector<Textbook*>();

    for (int i=0; i<books.size(); i++) {
        requiredBooks->append(books[i]);
    }
}

Course::~Course() {
    delete requiredBooks;
}

int Course::getCourseId() {
    return id;
}

void Course::setCourseId(int newId) {
    id = newId;
}

QString Course::getCourseCode() {
    return code;
}

void Course::setCourseCode(QString newCode) {
    code = newCode;
}

void Course::addRequiredText(Textbook *book) {
    requiredBooks->append(book);
}

QVector<Textbook*> Course::getRequiredTexts() {
    // Return a copy of the vector
    return QVector<Textbook*>( *(this->requiredBooks) );
}

QString Course::getCourseName() const
{
    return name;
}

void Course::setCourseName(const QString &value)
{
    name = value;
}

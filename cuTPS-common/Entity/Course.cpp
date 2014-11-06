#include "Course.h"

Course::Course() {
    code = "";
    requiredBooks = new QVector<Textbook*>();
}

Course::Course(QString course) {
    code = course;
    name = "";
    requiredBooks = new QVector<Textbook*>();
}

Course::Course(QString course, QString courseName, QVector<Textbook*> books) {
    code = course;
    name = courseName;
    requiredBooks = new QVector<Textbook*>();

    for (int i=0; i<books.size(); i++) {
        requiredBooks->append(books[i]);
    }
}

Course::~Course() {
    delete requiredBooks;
}

int Course::getId() const {
    return id;
}

void Course::setId(const int newId) {
    id = newId;
}

QString Course::getCourseCode() const {
    return code;
}

void Course::setCourseCode(const QString newCode) {
    code = newCode;
}

void Course::addRequiredText(Textbook *book) {
    requiredBooks->append(book);
}

QVector<Textbook*>* Course::getRequiredTexts() const {
    // Return a pointer to the vector contatining books
    return this->requiredBooks;
}

QString Course::getCourseName() const
{
    return name;
}

void Course::setCourseName(const QString &value)
{
    name = value;
}

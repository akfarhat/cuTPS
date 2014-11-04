#include "Student.h"

Student::Student(int id, QString name, QString username, int studentNum) : User(id, name, username), studentNumber(studentNum) {

}

Student::~Student() {}

int Student::getStudentNumber() {
    return studentNumber;
}

void Student::setStudentNumber(int newNumber) {
    studentNumber = newNumber;
}

QString Student::getEmailAddress() {
    return emailAddress;
}

void Student::setEmailAddress(QString newEmail) {
    emailAddress = newEmail;
}

QVector<Course*> Student::getCourses() {
    return courses;
}

void Student::enrollInCourse(Course *newCourse) {
    courses.append(newCourse);
}

QString Student::getDetails() {
    QString details = "";
    details += "Type: Student\nUser ID: ";
    details += QString::number(this->getUserId());
    details += "\nUsername: ";
    details += this->getUsername();
    details += "\nName: ";
    details += this->getName();
    details += "\nStudent Number: ";
    details += QString::number(this->getStudentNumber());
    details += "\nEmail Address: ";
    details += this->getEmailAddress();
    details += "\nCourses Enrolled in: ";

    foreach(Course *course, this->getCourses()) {
        details += course->getCourseCode();
        details += ", ";
    }
    details += "\n";

    return details;
}

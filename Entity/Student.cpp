#include "Student.h"

Student::Student(QString name, QString username) : User(name, username) {

}

Student::~Student() {}

int Student::getStudentNumber() {
    return studentNumber;
}

QString Student::getEmailAddress() {
    return emailAddress;
}

QString Student::getType() {
    return "Student";
}

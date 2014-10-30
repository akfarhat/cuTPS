#include "Student.h"

Student::Student(QString name, QString username) : User(name, username) {

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

QString Student::getType() {
    return "Student";
}

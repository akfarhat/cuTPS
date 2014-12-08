#include "Student.h"

Student::Student()
{}

Student::Student(int id, QString name, QString username, int studentNum)
    : User(id, name, username), studentNumber(studentNum)
{
    cart = new ShoppingCart();
    billing = nullptr;
    delivery = nullptr;
}

Student::~Student() {
    delete cart;

    if (billing) {
        delete billing;
    }
    if (delivery) {
        delete delivery;
    }
}

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

QVector<qint32>& Student::getCourses() {
    return courseIds;
}

CreditCardInfo* Student::getCreditCardInfo() {
    return billing;
}

void Student::setCreditCardInfo(CreditCardInfo *info) {
    if (billing)
        delete billing;

    billing = info;
}

DeliveryInfo* Student::getDeliveryInfo() {
    return delivery;
}

void Student::setDeliveryInfo(DeliveryInfo *info) {
    if (delivery)
        delete delivery;
    delivery = info;
}

void Student::enrollInCourse(qint32 courseId) {
    courseIds.append(courseId);
}

ShoppingCart* Student::getCart() {
    return cart;
}

void Student::setCart(ShoppingCart *newCart) {
    cart = newCart;
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

    foreach(qint32 cid, this->getCourses()) {
        details += QString::number(cid);
        details += ", ";
    }
    details += "\n";

    return details;
}

QDataStream& operator<<(QDataStream& os, const Student& s)
{
    os.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    os << dynamic_cast<const User&>(s);
    os << static_cast<qint32>(s.studentNumber);
    os << s.emailAddress
       << s.courseIds;

    if (s.billing)
    {
        os << (qint8) 1; // presence flag
        os << *s.billing;
    } else {
        os << (qint8) 0; // i.e. billinginfo not present
    }

    if (s.delivery)
    {
        os << (qint8) 1;
        os << *s.delivery;
    } else {
        os << (qint8) 0;
    }

    return os;
}

QDataStream& operator>>(QDataStream& is, Student& s)
{
    is.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    is >> dynamic_cast<User&>(s);
    is >> s.studentNumber;
    is >> s.emailAddress
       >> s.courseIds;

    qint8 presenceFlag;
    is >> presenceFlag;

    if (presenceFlag)
    {
        CreditCardInfo* cc = new CreditCardInfo();
        is >> *cc;
        s.setCreditCardInfo(cc);
    }

    is >> presenceFlag;

    if (presenceFlag)
    {
        DeliveryInfo* di = new DeliveryInfo();
        is >> *di;
        s.setDeliveryInfo(di);
    }

    return is;
}

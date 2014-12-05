// Class: Student
// Type: Entity
// Description:
//     Represents the type of user that can browse
//     and order the content offered in the system for
//     courses that they are registed in.

#ifndef STUDENT_H
#define STUDENT_H

#include "User.h"
#include "Course.h"
#include "ShoppingCart.h"
#include "CreditcardInfo.h"
#include "DeliveryInfo.h"
#include <QString>
#include <QVector>

using namespace std;

class Student: public User {

    private:
        int studentNumber;
        QString emailAddress;
        QVector<Course*> courses;
        ShoppingCart *cart;
        CreditCardInfo *billing;
        DeliveryInfo *delivery;



    public:
        Student(int, QString, QString, int);
        ~Student();

        int getStudentNumber();
        void setStudentNumber(int);

        QString getEmailAddress();
        void setEmailAddress(QString);

        QVector<Course*> getCourses();
        void enrollInCourse(Course*);

        ShoppingCart* getCart();
        void setCart(ShoppingCart*);

        CreditCardInfo* getCreditCardInfo();
        void setCreditCardInfo(CreditCardInfo*);

        DeliveryInfo* getDeliveryInfo();
        void setDeliveryInfo(DeliveryInfo*);

        QString getDetails();
};

#endif // STUDENT_H

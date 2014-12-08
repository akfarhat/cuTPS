// Class: Student
// Type: Entity
// Description:
//     Represents the type of user that can browse
//     and order the content offered in the system for
//     courses that they are registed in.

#ifndef STUDENT_H
#define STUDENT_H

#include "libcutps_global.h"

#include "User.h"
#include "Course.h"
#include "ShoppingCart.h"
#include "CreditCardInfo.h"
#include "DeliveryInfo.h"
#include <QString>
#include <QVector>

using namespace std;

class LIBCUTPS_EXPORT Student : public User {
public:
    Student();
    Student(int, QString, QString, int);
    ~Student();

    int getStudentNumber();
    void setStudentNumber(int);

    QString getEmailAddress();
    void setEmailAddress(QString);

    QVector<qint32>& getCourses();
    void enrollInCourse(qint32 cId);

    ShoppingCart* getCart();
    void setCart(ShoppingCart*);

    CreditCardInfo* getCreditCardInfo();
    void setCreditCardInfo(CreditCardInfo*);

    DeliveryInfo* getDeliveryInfo();
    void setDeliveryInfo(DeliveryInfo*);

    QString getDetails();

    // Serialization routines
    friend QDataStream& operator<<(QDataStream& os, const Student& s); // output
    friend QDataStream& operator>>(QDataStream& is, Student& s); // input

private:
    int studentNumber;
    QString emailAddress;
    QVector<qint32> courseIds;
    ShoppingCart *cart;
    CreditCardInfo *billing;
    DeliveryInfo *delivery;
};

#endif // STUDENT_H

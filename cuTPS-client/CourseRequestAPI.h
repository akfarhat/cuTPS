// Class: CourseRequestAPI
// Description:
//   Used to interface all networking requests in
//   the CourseManagement subsystem to the
//   ClientNetwokring subsystem, reducing coupling.
// Traceability:
//   CourseRequestAPI class
//   in the CourseManagement subsystem

#ifndef COURSEREQUESTAPI_H
#define COURSEREQUESTAPI_H

#include <QObject>
#include <QVector>

#include "ClientNetworkHandler.h"
#include "Entity/Course.h"

class CourseRequestAPI : public QObject
{
    Q_OBJECT
public:
    explicit CourseRequestAPI(QObject *parent = 0,
                              ClientNetworkHandler *net = NULL);
    QUuid getAllCourses();
    QUuid getAllBooks();
    QUuid getBookDetails(const QVector<qint32> &) const;
    QUuid addCourse(Course&);
    QUuid modifyCourse(Course &);
    QUuid deleteCourse(int);
    QUuid linkText(int, int);
    QUuid unlinkText(int, int);

signals:

public slots:

private:
    ClientNetworkHandler *networking;

};

#endif // COURSEREQUESTAPI_H

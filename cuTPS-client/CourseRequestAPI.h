// Traceability:
//   CourseRequestAPI class
//   in the CourseManagement subsystem

#ifndef COURSEREQUESTAPI_H
#define COURSEREQUESTAPI_H

#include <QObject>

#include "ClientNetworkHandler.h"
#include "Entity/Course.h"

class CourseRequestAPI : public QObject
{
    Q_OBJECT
public:
    explicit CourseRequestAPI(QObject *parent = 0,
                              ClientNetworkHandler *net = NULL);
    QUuid addCourse(Course&);
    QUuid linkText(int, int);
    QUuid unlinkText(int, int);

signals:

public slots:

private:
    ClientNetworkHandler *networking;

};

#endif // COURSEREQUESTAPI_H

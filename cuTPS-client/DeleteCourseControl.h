// Traceability:
//   DeleteCourseControl class in the CourseManagement subsystem

#ifndef DELETECOURSECONTROL_H
#define DELETECOURSECONTROL_H

#include <QObject>

#include "CourseRequestAPI.h"

class DeleteCourseControl : QObject
{
    Q_OBJECT

public:
    DeleteCourseControl(CourseRequestAPI *);
    void deleteCourse(QUuid &, int);

private:
    CourseRequestAPI *requestAPI;
};

#endif // DELETECOURSECONTROL_H

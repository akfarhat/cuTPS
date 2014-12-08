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

private:
    CourseRequestAPI *requestAPI;
    void deleteCourse(QUuid &, int);
};

#endif // DELETECOURSECONTROL_H

#include "DeleteCourseControl.h"

DeleteCourseControl::DeleteCourseControl(CourseRequestAPI *api) :
    requestAPI(api)
{
}

void DeleteCourseControl::deleteCourse(QUuid &uid, int courseId)
{
    uid = requestAPI->deleteCourse(courseId);
}

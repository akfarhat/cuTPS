#include "ModifyCourseControl.h"

ModifyCourseControl::ModifyCourseControl(CourseRequestAPI *api) :
    requestAPI(api)
{
}

void ModifyCourseControl::modifyCourse(QUuid &uid, Course &c)
{
    uid = requestAPI->modifyCourse(c);
}

#include "AddCourseControl.h"

AddCourseControl::AddCourseControl(CourseRequestAPI *serverAPI)
    : api(serverAPI)
{}

AddCourseControl::~AddCourseControl() {

}

void AddCourseControl::addCourse(QUuid &reqId, Course &newCourse) {
    reqId = api->addCourse(newCourse);
}

#include "AddCourseControl.h"

AddCourseControl::AddCourseControl() {

}

AddCourseControl::~AddCourseControl() {

}

void AddCourseControl::addCourse(QUuid &reqId, Course &newCourse) {
    reqId = network.addCourse(newCourse);
}

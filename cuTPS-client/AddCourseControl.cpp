#include "AddCourseControl.h"

AddCourseControl::AddCourseControl() {

}

AddCourseControl::~AddCourseControl() {

}

void AddCourseControl::addCourse(SessionCredentials *sessionCreds, Course *newCourse, ServerResponse *response) {
    network.addCourse(sessionCreds, newCourse, response);
}

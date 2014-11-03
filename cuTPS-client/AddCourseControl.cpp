#include "AddCourseControl.h"

AddCourseControl::AddCourseControl(ClientNetworkHandler &serverAPI)
    : network(serverAPI)
{}

AddCourseControl::~AddCourseControl() {

}

void AddCourseControl::addCourse(QUuid &reqId, Course &newCourse) {
    reqId = network.addCourse(newCourse);
}

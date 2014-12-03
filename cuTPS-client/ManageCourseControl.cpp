#include "ManageCourseControl.h"
#include "ContentManagementInterface.h"

ManageCourseControl::ManageCourseControl(ContentManagementInterface *cmIf,
                                         ClientNetworkHandler *net)
{
    this->networking = net;

    this->cmIF = cmIf;

    this->requestAPI = new CourseRequestAPI(0, networking);

    this->courseDetailsWin = new CourseDetailsWindow(0, this, requestAPI);

    this->courseDetailsWin->show();

    // When a management window clicks back, we want the original menu interface.
    connect(this->courseDetailsWin, SIGNAL(courseNavigateBack()),
            this->cmIF, SLOT(courseNavigateBack()));

    // TODO: connect slots for requests that the networking will signal
}

ManageCourseControl::~ManageCourseControl()
{
    delete this->courseDetailsWin;
    delete this->requestAPI;
}

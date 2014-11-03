// Class: AddCourseControl
// Type: Control
// Description:
//     This class is responsible for invoking the client
//     side API method in the network handler for adding
//     a course to availability.

#ifndef ADDCOURSECONTROL_H
#define ADDCOURSECONTROL_H

#include "Utils.h"
#include "ClientNetworkHandler.h"
#include "Entity/Course.h"

class AddCourseControl {

    private:
        ClientNetworkHandler &network;

    public:
        AddCourseControl(ClientNetworkHandler &);
        ~AddCourseControl();

        // Add the course to availability through the
        // network handler, return the request identifier
        void addCourse(QUuid &, Course &);
};

#endif // ADDCOURSECONTROL_H
// Class: AddCourseControl
// Type: Control
// Description:
//     This class is responsible for invoking the client
//     side API method in the network handler for adding
//     a course to availability.
// Traceability:
//   The AddCourseControl class in the CourseManagement subsystem.

#ifndef ADDCOURSECONTROL_H
#define ADDCOURSECONTROL_H

#include "Defines.h"
#include "CourseRequestAPI.h"
#include "Entity/Course.h"

class AddCourseControl {

    private:
        CourseRequestAPI *api;

    public:
        AddCourseControl(CourseRequestAPI *);
        ~AddCourseControl();

        // Add the course to availability through the
        // network handler, return the request identifier
        void addCourse(QUuid &, Course &);
};

#endif // ADDCOURSECONTROL_H

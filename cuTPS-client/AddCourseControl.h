#ifndef ADDCOURSECONTROL_H
#define ADDCOURSECONTROL_H

#include "Utils.h"
#include "ClientNetworkHandler.h"
#include "Entity/Course.h"

class AddCourseControl {

    private:
        ClientNetworkHandler network;

    public:
        AddCourseControl();
        ~AddCourseControl();

        void addCourse(QUuid &, Course &);
};

#endif // ADDCOURSECONTROL_H

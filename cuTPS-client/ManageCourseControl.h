// Traceability:
//   ManageCourseControl class,
//   formally the ModifyCourseControl and
//   AddCourseControl classes from the
//   CourseManagement subsystem

#ifndef MANAGECOURSECONTROL_H
#define MANAGECOURSECONTROL_H

#include <QObject>

#include "CourseDetailsWindow.h"
#include "CourseRequestAPI.h"
#include "ClientNetworkHandler.h"

// Forward reference to avoid cyclical references
class ContentManagementInterface;

class ManageCourseControl : public QObject
{
    private:
        Q_OBJECT

    public:
        ManageCourseControl(ContentManagementInterface *, ClientNetworkHandler *);
        ~ManageCourseControl();

    private:
        ClientNetworkHandler *networking;
        CourseRequestAPI *requestAPI;
        CourseDetailsWindow *courseDetailsWin;
        ContentManagementInterface *cmIF;
};

#endif // MANAGECOURSECONTROL_H

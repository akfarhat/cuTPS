// Traceability:
//   ManageCourseControl class,
//   formally the ModifyCourseControl and
//   AddCourseControl classes from the
//   CourseManagement subsystem

#ifndef MANAGECOURSECONTROL_H
#define MANAGECOURSECONTROL_H

#include <QObject>
#include <QString>
#include <QVector>

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

    public slots:
        // Emitted by the save button in the new course
        // dialog, spawned from CourseDetailsWindow
        void saveNewCourse(QString, QString);
        void modifyCourse(int, QString, QString);
        void deleteCourse(int);
        void removeRequiredBook(int, int);
        // From the AddRequiredBooksWindow
        void addRequiredBooks(QVector<int>&, int);

    private:
        ClientNetworkHandler *networking;
        CourseRequestAPI *requestAPI;
        CourseDetailsWindow *courseDetailsWin;
        ContentManagementInterface *cmIF;
};

#endif // MANAGECOURSECONTROL_H

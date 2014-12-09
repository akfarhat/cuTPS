#include "ManageCourseControl.h"
#include "ContentManagementInterface.h"
#include "AddCourseControl.h"
#include "ModifyCourseControl.h"
#include "DeleteCourseControl.h"


#include <QDebug>

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

    connect(this->courseDetailsWin, SIGNAL(modifyCourse(int,QString,QString)),
            this, SLOT(modifyCourse(int,QString,QString)));

    connect(this->courseDetailsWin, SIGNAL(deleteCourse(int)),
            this, SLOT(deleteCourse(int)));

    connect(this->courseDetailsWin, SIGNAL(removeRequiredBook(int,int)),
            this, SLOT(removeRequiredBook(int, int)));

    // Connect networking responses to the window controls that required the data
    connect(this->networking, SIGNAL(courseListReceived(QUuid,int,QList<Course*>*)),
            this->courseDetailsWin, SLOT(courseListReceived(QUuid,int,QList<Course*>*)));

    connect(this->networking, SIGNAL(textbookListReceived(QUuid,int,QList<Textbook*>*)),
            this->courseDetailsWin, SLOT(textbookListReceived(QUuid,int,QList<Textbook*>*)));

    connect(this->networking, SIGNAL(updateCompleted(QUuid,int,InvocationDescriptor,qint32)),
            this->courseDetailsWin, SLOT(updateCompleted(QUuid,int,InvocationDescriptor,qint32)));
}

ManageCourseControl::~ManageCourseControl()
{
    delete this->courseDetailsWin;
    delete this->requestAPI;
}

void ManageCourseControl::saveNewCourse(QString code, QString name)
{
    qDebug() << "Saving new course " << code << ": " << name;

    AddCourseControl ctrl(this->requestAPI);

    Course c(code, name);

    // TODO: we are not currently handling the response for this
    QUuid reqId;
    ctrl.addCourse(reqId, c);
}

void ManageCourseControl::modifyCourse(int courseId,
                                       QString courseCode,
                                       QString courseName)
{
    qDebug() << "Modifying existing course id=" << courseId
             << " code = " << courseCode
             << " name = " << courseName;

    ModifyCourseControl ctrl(this->requestAPI);

    Course c(courseCode, courseName);

    // TODO: not currently handling response
    QUuid reqId;
    ctrl.modifyCourse(reqId, c);
}

void ManageCourseControl::deleteCourse(int courseId)
{
    qDebug() << "Deleting course with ID = " << courseId;

    DeleteCourseControl delCtrl(this->requestAPI);

    // TODO: not currently handling response
    QUuid reqId;
    delCtrl.deleteCourse(reqId, courseId);
}

void ManageCourseControl::removeRequiredBook(int bookId, int courseId)
{
    qDebug() << "Removing book with id=" << bookId
             << " from required texts for course id=" << courseId;

    // TODO: ignoring response from this request
    this->requestAPI->unlinkText(courseId, bookId);

    // TODO: refresh required book list in courseDetailsWin
}

void ManageCourseControl::addRequiredBooks(QVector<int>& books, int courseId)
{
    for (int id: books) {
        qDebug() << "Adding bookId = " << id
                 << " as required text for course ID = " << courseId;

        // TODO: ignoring response from this request
        this->requestAPI->linkText(courseId, id);

        // TODO: refresh required book list in courseDetailsWin
    }
}

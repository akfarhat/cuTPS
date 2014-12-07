#include "ManageCourseControl.h"
#include "ContentManagementInterface.h"
#include "AddCourseControl.h"

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

    // TODO: connect slots for requests that the networking will signal
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
    QUuid id;
    ctrl.addCourse(id, c);

    this->courseDetailsWin->displayCourseList();
}

void ManageCourseControl::modifyCourse(int courseId,
                                       QString courseCode,
                                       QString courseName)
{
    qDebug() << "Modifying existing course id=" << courseId
             << " code = " << courseCode
             << " name = " << courseName;
    // TODO: create a modifyCourseControl to handle the request
}

void ManageCourseControl::deleteCourse(int courseId)
{
    qDebug() << "Deleting course with ID = " << courseId;

    // TODO: create a deleteCourseControl object to handle request
}

void ManageCourseControl::removeRequiredBook(int bookId, int courseId)
{
    qDebug() << "Removing book with id=" << bookId
             << " from required texts for course id=" << courseId;

    // TODO: ignoring response from this request
    this->requestAPI->unlinkText(courseId, bookId);
}

void ManageCourseControl::addRequiredBooks(QVector<int>& books, int courseId)
{
    for (int id: books) {
        qDebug() << "Adding bookId = " << id
                 << " as required text for course ID = " << courseId;

        // TODO: ignoring response from this request
        this->requestAPI->linkText(courseId, id);
    }
}

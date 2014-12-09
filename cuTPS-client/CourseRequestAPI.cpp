#include "CourseRequestAPI.h"

#include <QDebug>

CourseRequestAPI::CourseRequestAPI(QObject *parent,
                                   ClientNetworkHandler *net) :
    QObject(parent)
{
    this->networking = net;
}


QUuid CourseRequestAPI::getAllCourses()
{
    return this->networking->getAllCourses();
}

QUuid CourseRequestAPI::getBookDetails(const QVector<qint32> &bookIds) const
{
    return this->networking->getBookDetails(bookIds);
}

QUuid CourseRequestAPI::addCourse(Course &c)
{
    return this->networking->addCourse(c);
}

QUuid CourseRequestAPI::modifyCourse(Course &c)
{
    // This add should result in an update since the id is set
    return this->networking->addCourse(c);
}

QUuid CourseRequestAPI::linkText(int courseId, int textId)
{
    return this->networking->linkTextbook(courseId, textId);
}

QUuid CourseRequestAPI::unlinkText(int courseId, int textId)
{
    return this->networking->unlinkTextbook(courseId, textId);
}

QUuid CourseRequestAPI::deleteCourse(int courseId)
{
    return this->networking->removeCourse(courseId);
}

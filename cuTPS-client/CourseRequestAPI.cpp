#include "CourseRequestAPI.h"

#include <QDebug>

CourseRequestAPI::CourseRequestAPI(QObject *parent,
                                   ClientNetworkHandler *net) :
    QObject(parent)
{
    this->networking = net;
}


QUuid CourseRequestAPI::addCourse(Course &c)
{
    qDebug() << "TODO: handle add Course from ClientNetworkHandler";
    QUuid id;
    return id;
}

QUuid CourseRequestAPI::linkText(int courseId, int textId)
{
    this->networking->linkTextbook(courseId, textId);
}

QUuid CourseRequestAPI::unlinkText(int courseId, int textId)
{
    this->networking->unlinkTextbook(courseId, textId);
}

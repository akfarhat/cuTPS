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

#include "AddCourseTask.h"

#include <QDebug>

AddCourseTask::AddCourseTask(Server* srv)
    : WorkerTask(srv)
{
}

void AddCourseTask::run()
{
    qDebug() << "Add course task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request->getRequestId();

    Course course;
    QDataStream in(request->getData(), QIODevice::ReadOnly);

    in >> course;

    qDebug() << "TPSAddCourseTask deserialized course:";
    qDebug() << " courseCode = " << course.getCourseCode();
    qDebug() << " course name = " << course.getCourseName();
    qDebug() << " id = " << QString::number(course.getId());

    qDebug() << "TPSAddCourseTask calling server addCourse API";

    ServerResponse r = server->addCourse(sessionId, course);

    qDebug() << "TPSAddCourseTask finished server API call";

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    response->setResponseCode(r.code == Fail ? 0x0 : 0x1);
    response->setSessionId(sessionId);

    emit result(response->getResponseCode(), response);
}



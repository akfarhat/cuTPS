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
    qint32 courseId;
    ServerResponse r;
    QDataStream in(request->getData(), QIODevice::ReadOnly);

    in >> course;

    courseId = course.getId();

    if (courseId < 0) {
        r = server->addCourse(sessionId, course, courseId);
    } else {
        r = server->replaceCourse(sessionId, courseId, course);
    }

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    response->setResponseCode(r.code == Fail ? 0x0 : 0x1);
    response->setSessionId(sessionId);

    if (response->getResponseCode() > 0)
    {
        QByteArray responseDataBytes;
        QDataStream outData(&responseDataBytes, QIODevice::WriteOnly);
        outData << courseId;
        response->setData(responseDataBytes);
    }

    emit result(response->getResponseCode(), response);
}



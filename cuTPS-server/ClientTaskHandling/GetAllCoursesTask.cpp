#include "GetAllCoursesTask.h"

#include <QDebug>
#include <QUuid>
#include <QByteArray>
#include <QDataStream>

#include "Entity/NetResponse.h"
#include "Entity/Course.h"

GetAllCoursesTask::GetAllCoursesTask(Server* srv)
    : WorkerTask(srv)
{
}

void GetAllCoursesTask::run()
{
    qDebug() << "GetAllCourses task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request->getRequestId();

    QVector<Course> courses;

    // TODO: handle the result of getAllCourses
    ServerResponse getCourses = server->getAllCourses(sessionId, courses);

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    response->setResponseCode(getCourses.code == Fail ? 0x0 : 0x1);
    response->setSessionId(sessionId);

    QByteArray responseDataBytes;
    QDataStream outData(&responseDataBytes, QIODevice::WriteOnly);

    outData << static_cast<qint32>(courses.size());
    for (Course cour : courses)
        outData << cour;

    response->setData(responseDataBytes);

    emit result(response->getResponseCode(), response);
}


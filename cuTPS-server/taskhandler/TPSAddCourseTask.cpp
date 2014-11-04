#include "TPSAddCourseTask.h"

#include <QDebug>

TPSAddCourseTask::TPSAddCourseTask(Server* srv)
    : TPSWorkerTask(srv)
{
}

void TPSAddCourseTask::run()
{
    qDebug() << "Add course task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request.requestId;

    Course course("blablabla"); // give me a default constructor pls

    QDataStream in(iblock, QIODevice::ReadOnly);
    parseCourse(&course, &in);

    ServerResponse r = server->addCourse(sessionId, course);

    TPSNetProtocol::NetResponse response;
    QByteArray data;
    QDataStream out(oblock, QIODevice::WriteOnly);

    setupResponse(response,
                  r.code == Fail ? 0x0 : 0x1,
                  &data,
                  &out);

    emit result(response.responseCode, oblock);
}

void TPSAddCourseTask::parseCourse(Course*, QDataStream*)
{

}



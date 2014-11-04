#include "TPSAddCourseTask.h"
#include "TPSNetUtils.h"

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
    TPSNetUtils::DeserializeCourse(&course, &in);

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



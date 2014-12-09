


#include "RemoveCourseTask.h"

#include <QDataStream>
#include <QDebug>

#include "Defines.h"

RemoveCourseTask::RemoveCourseTask(Server* srv)
    : WorkerTask(srv)
{
}

void RemoveCourseTask::run()
{
    qDebug() << "Remove item task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request->getRequestId();

    QDataStream in(request->getData(), QIODevice::ReadOnly);
    qint32 courseId;
    in >> courseId;

    // TODO: Implement
    // ServerResponse r = server->removeCourse(sessionId, courseId);
    ServerResponse r; r.code = Fail;

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

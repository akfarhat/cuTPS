#include "BookLinkTask.h"

#include <QDebug>

#include "Defines.h"

using namespace TPSNetProtocolDef;

BookLinkTask::BookLinkTask(Server* srv)
    : WorkerTask(srv)
{
}

void BookLinkTask::run()
{
    qDebug() << "Book link unlink task run!";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request->getRequestId();

    QDataStream in(request->getData(), QIODevice::ReadOnly);

    qint32 courseId, textId;

    in >> courseId >> textId;

    ServerResponse r;
    switch (request->getInvocation())
    {

    case IBookLink:
    {
        r = server->linkTextbook(sessionId, courseId, textId);
        break;
    }

    case IBookUnlink:
    {
        r = server->unlinkTextbook(sessionId, courseId, textId);
        break;
    }

    default:
        r.code = Fail;
        break;
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
        outData << textId;
        response->setData(responseDataBytes);
    }

    emit result(response->getResponseCode(), response);
}


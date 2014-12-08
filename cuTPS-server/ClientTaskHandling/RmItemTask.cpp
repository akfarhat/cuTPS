#include "RmItemTask.h"

#include <QDebug>

#include "Defines.h"

using namespace TPSNetProtocolDef;

RmItemTask::RmItemTask(Server* srv)
    : WorkerTask(srv)
{
}

void RmItemTask::run()
{
    qDebug() << "Remove item task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request->getRequestId();

    QDataStream in(request->getData(), QIODevice::ReadOnly);
    qint32 itemId;
    in >> itemId;

    ServerResponse r;
    switch (request->getInvocation())
    {

    case IRmBook:
    {
        // TODO: implement this
        //r = server->removeBook(sessionId, itemId);
        r.code = Fail;
        break;
    }

    case IRmChapter:
    {
        // TODO: implement this
        //r = server->removeChapter(sessionId, itemId);
        r.code = Fail;
        break;
    }

    case IRmSection:
    {
        // TODO: implement this
        // r = server->removeSection(sessionId, itemId);
        r.code = Fail;
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

    emit result(response->getResponseCode(), response);
}


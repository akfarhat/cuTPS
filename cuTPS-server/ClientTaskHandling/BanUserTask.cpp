#include "BanUserTask.h"

#include <QDebug>

#include "Defines.h"

BanUserTask::BanUserTask(Server* srv)
    : WorkerTask(srv)
{
}

void BanUserTask::run()
{
    qDebug() << "Ban user task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request->getRequestId();

    QDataStream in(request->getData(), QIODevice::ReadOnly);

    qint32 uid;
    in >> uid;

    // TODO: implement this
    // ServerResponse r = server->banUser(sessionId, uid);

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    //response->setResponseCode(r.code == Fail ? 0x0 : 0x1);
    response->setResponseCode(0x0); // rm this
    response->setSessionId(sessionId);

    emit result(response->getResponseCode(), response);
}


#include "AddUserTask.h"

#include <QDebug>
#include <QUuid>
#include <QByteArray>
#include <QDataStream>

#include "Entity/NetResponse.h"
#include "Entity/User.h"

AddUserTask::AddUserTask(Server* srv)
    : WorkerTask(srv)
{
}

void AddUserTask::run()
{
    qDebug() << "AddUserTask task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request->getRequestId();

    QDataStream in(request->getData(), QIODevice::ReadOnly);
    User usr;

    // TODO: User serialization
    // in >> usr;

    // TODO implement this
    //ServerResponse r = server->addUser(sessionId, usr);
    ServerResponse r; r.code = Fail;

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    response->setResponseCode(r.code == Fail ? 0x0 : 0x1);
    response->setSessionId(sessionId);

    emit result(response->getResponseCode(), response);
}

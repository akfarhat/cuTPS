#include <QTcpSocket>

#include "WorkerTask.h"
#include "Defines.h"
#include <ServerNetworking/NetClient.h>

WorkerTask::WorkerTask(Server* srv)
{
    server = srv;
}

void WorkerTask::setSessionId(QUuid sessionId)
{
    this->sessionId = sessionId;
}

void WorkerTask::setRequest(NetRequest* request)
{
    this->request = request;
}

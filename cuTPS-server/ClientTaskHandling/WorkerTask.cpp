#include "WorkerTask.h"

WorkerTask::WorkerTask(Server* srv)
{
    server = srv;
}

WorkerTask::~WorkerTask()
{
    if (request) delete request;
}

void WorkerTask::setSessionId(QUuid sessionId)
{
    this->sessionId = sessionId;
}

void WorkerTask::setRequest(NetRequest* request)
{
    this->request = request;
}


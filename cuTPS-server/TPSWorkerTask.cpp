#include <QTcpSocket>

#include "TPSWorkerTask.h"
#include "Defines.h"
#include "TPSClient.h"

TPSWorkerTask::TPSWorkerTask(Server* srv)
{
    server = srv;
}

void TPSWorkerTask::setSessionId(QUuid sessionId)
{
    this->sessionId = sessionId;
}

void TPSWorkerTask::setRequest(TPSNetProtocol::NetRequest& request)
{
    this->request = request;
}

void TPSWorkerTask::setInputDataBlock(QByteArray* idata)
{
    this->iblock = idata;
}

void TPSWorkerTask::setResponseDataBlock(QByteArray* odata)
{
    this->oblock = odata;
}

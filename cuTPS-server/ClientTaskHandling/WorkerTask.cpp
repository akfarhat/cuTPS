#include <QTcpSocket>

#include "TPSNetUtils.h"

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

void WorkerTask::setRequest(TPSNetProtocol::NetRequest& request)
{
    this->request = request;
}

void WorkerTask::setInputDataBlock(QByteArray* idata)
{
    this->iblock = idata;
}

void WorkerTask::setResponseDataBlock(QByteArray* odata)
{
    this->oblock = odata;
}

void WorkerTask::setupResponse(TPSNetProtocol::NetResponse& response,
                                  qint8 code,
                                  QByteArray* dataBlock,
                                  QDataStream* outStream)
{
    response.invocation = request.invocation;
    response.requestId = request.requestId;
    response.sessionId = sessionId;
    response.responseCode = code;
    response.data = dataBlock;

    // TODO: this can be removed or moved to a more verbose output
    qDebug() << "TPSWorkerTask::setupResponse -- "
             << "invocation: " << response.invocation
             << ", requestId: " << response.requestId
             << ", sessionId: " << response.sessionId
             << ", responseCode: " << response.responseCode;

    TPSNetUtils::SerializeResponse(outStream, &response);
}

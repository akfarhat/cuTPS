#include <QTcpSocket>

#include "TPSNetUtils.h"

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

void TPSWorkerTask::setupResponse(TPSNetProtocol::NetResponse& response,
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

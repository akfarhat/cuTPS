#include "SubmitOrderTask.h"
#include "Entity/Order.h"

#include <QDebug>

SubmitOrderTask::SubmitOrderTask(Server* srv)
    : WorkerTask(srv)
{
}

void SubmitOrderTask::run()
{
    qDebug() << "Submit order task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request->getRequestId();

    Order* order = new Order();
    QDataStream in(request->getData(), QIODevice::ReadOnly);

    in >> *order;

    ServerResponse r = server->submitOrder(sessionId, *order);

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    response->setResponseCode(0x1);
    response->setSessionId(sessionId);

    emit result(response->getResponseCode(), response);
}


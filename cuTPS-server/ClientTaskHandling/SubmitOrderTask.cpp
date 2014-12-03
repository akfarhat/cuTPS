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

    Order order;
    QDataStream in(request->getData(), QIODevice::ReadOnly);

    in >> order;

    ServerResponse r = server->submitOrder(sessionId, order);

    NetResponse response = NetResponse(*request);
    response.setResponseCode(r.code == Fail ? 0x0 : 0x1);
    response.setSessionId(sessionId);

    QByteArray* responseBytes = new QByteArray();   // NetClient will delete it
    QDataStream out(responseBytes, QIODevice::WriteOnly);

    out << response;

    emit result(response.getResponseCode(), responseBytes);
}


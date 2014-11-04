#include "TPSSubmitOrderTask.h"
#include "Entity/Order.h"

#include <QDebug>

TPSSubmitOrderTask::TPSSubmitOrderTask(Server* srv)
    : TPSWorkerTask(srv)
{
}

void TPSSubmitOrderTask::run()
{
    qDebug() << "Submit order task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request.requestId;

    // Order order; // Default constructor?

    QDataStream in(iblock, QIODevice::ReadOnly);
    // parseOrder(&order, &in);

    //ServerResponse r = server->submitOrder(sessionId, order);

    TPSNetProtocol::NetResponse response;
    QByteArray data;
    QDataStream out(oblock, QIODevice::WriteOnly);

//    setupResponse(response,
//                  r.code == Fail ? 0x0 : 0x1,
//                  &data,
//                  &out);

    emit result(response.responseCode, oblock);
}


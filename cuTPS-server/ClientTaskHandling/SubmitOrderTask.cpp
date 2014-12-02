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
             << "Request: " << request.requestId;

    Order order;

    QDataStream in(iblock, QIODevice::ReadOnly);

    TPSNetUtils::DeserializeOrder(&order, &in);

    qDebug() << "TPSSubmitOrderTask calling server submitOrder API";

    ServerResponse r = server->submitOrder(sessionId, order);

    qDebug() << "TPSSubmitOrderTask finished server API call";

    TPSNetProtocol::NetResponse response;
    QByteArray data;
    QDataStream out(oblock, QIODevice::WriteOnly);

    qDebug() << "TPSSubmitOrderTask setting up response packet";

    setupResponse(response,
                  r.code == Fail ? 0x0 : 0x1,
                  &data,
                  &out);

    qDebug() << "TPSSubmitOrderTask emitting result";

    emit result(response.responseCode, oblock);
}


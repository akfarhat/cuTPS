#include "TPSGetRequiredBooksTask.h"

#include <QDebug>

TPSGetRequiredBooksTask::TPSGetRequiredBooksTask(Server* srv)
    : TPSWorkerTask(srv)
{
}

void TPSGetRequiredBooksTask::run()
{
    qDebug() << "GetRequiredBooks task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request.requestId;

    QString username;

    QDataStream in(iblock, QIODevice::ReadOnly);
    in >> username;

    ServerResponse r = server->getRequiredTextbooks(sessionId, username);

    // TODO: Get the list of required books based on User that belongs to current sessionId.
    //       Write the list as ByteArray into data.

    TPSNetProtocol::NetResponse response;
    QByteArray data;
    QDataStream out(oblock, QIODevice::WriteOnly);

    setupResponse(response,
                  r.code == Fail ? 0x0 : 0x1,
                  &data,
                  &out);

    emit result(response.responseCode, oblock);
}


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

    TPSNetProtocol::NetResponse response;
    QByteArray data;
    QDataStream out(oblock, QIODevice::WriteOnly);

    setupResponse(response,
                  r.code == Fail ? 0x0 : 0x1,
                  &data,
                  &out);

    emit result(response.responseCode, oblock);
}


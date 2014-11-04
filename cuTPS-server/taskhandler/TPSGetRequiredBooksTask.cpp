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

    QVector<int>* ids;
    ServerResponse r = server->getRequiredTextbooks(sessionId, username, ids);

    TPSNetProtocol::NetResponse response;
    QByteArray data;
    QDataStream out(oblock, QIODevice::WriteOnly);

    for (int i = 0; i < ids->size(); ++i)
    {
        out << ((qint32) ids->at(i));
    }

    setupResponse(response,
                  r.code == Fail ? 0x0 : 0x1,
                  &data,
                  &out);

    emit result(response.responseCode, oblock);
}


#include "GetRequiredBooksTask.h"

#include <QDebug>

GetRequiredBooksTask::GetRequiredBooksTask(Server* srv)
    : WorkerTask(srv)
{
}

void GetRequiredBooksTask::run()
{
    qDebug() << "GetRequiredBooks task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request->getRequestId();

    QString username;

    QDataStream in(request->getData(), QIODevice::ReadOnly);

    in >> username;

    QVector<qint32> ids;

    qDebug() << "calling the getRequiredTextbooks API for user " << username;

    ServerResponse getBooks = server->getRequiredTextbooks(sessionId, username, &ids);

    NetResponse response = NetResponse(*request);
    response.setResponseCode(getBooks.code == Fail ? 0x0 : 0x1);
    response.setSessionId(sessionId);

    QByteArray* responseBytes = new QByteArray();   // NetClient will delete it
    QByteArray responseDataBytes;
    QDataStream out(responseBytes, QIODevice::WriteOnly);
    QDataStream outData(&responseDataBytes, QIODevice::WriteOnly);

    if (getBooks.code == Success)
    {
        outData << static_cast<qint32>(ids.size());

        for (qint32 id : ids)
        {
            outData << id;
        }

        response.setData(responseDataBytes);
    }

    out << response;

    emit result(response.getResponseCode(), responseBytes);
}

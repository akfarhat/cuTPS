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

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    response->setResponseCode(getBooks.code == Fail ? 0x0 : 0x1);
    response->setSessionId(sessionId);

    QByteArray responseDataBytes;
    QDataStream outData(&responseDataBytes, QIODevice::WriteOnly);

    if (getBooks.code == Success)
    {
        outData << static_cast<qint32>(ids.size());

        for (qint32 id : ids)
        {
            outData << id;
        }

        response->setData(responseDataBytes);
    }

    emit result(response->getResponseCode(), response);
}


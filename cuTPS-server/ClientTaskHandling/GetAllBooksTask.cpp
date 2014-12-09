#include "GetAllBooksTask.h"

#include <QDebug>
#include <QUuid>
#include <QByteArray>
#include <QDataStream>

#include "Entity/NetResponse.h"

GetAllBooksTask::GetAllBooksTask(Server* srv)
    : WorkerTask(srv)
{
}

void GetAllBooksTask::run()
{
    qDebug() << "GetAllBooks task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request->getRequestId();

    QVector<Textbook> books;
    ServerResponse getBooks = server->getAllTextbooks(sessionId, books);

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    response->setResponseCode(getBooks.code == Fail ? 0x0 : 0x1);
    response->setSessionId(sessionId);

    QByteArray responseDataBytes;
    QDataStream outData(&responseDataBytes, QIODevice::WriteOnly);

    if (getBooks.code == Success)
    {
        outData << static_cast<qint32>(books.size());

        for (Textbook t : books)
        {
            outData << t;
        }

        response->setData(responseDataBytes);
    } else {
        outData << static_cast<qint32>(0);
    }

    emit result(response->getResponseCode(), response);
}


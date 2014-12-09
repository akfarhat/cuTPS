#include "GetAllBooksTask.h"

#include <QDebug>
#include <QUuid>
#include <QByteArray>
#include <QDataStream>
#include <QtAlgorithms>

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

    QVector<Textbook*> books;
    ServerResponse getBooks = server->getAllTextbooks(sessionId, books);

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    response->setResponseCode(getBooks.code == Fail ? 0x0 : 0x1);
    response->setSessionId(sessionId);

    QByteArray responseDataBytes;
    QDataStream outData(&responseDataBytes, QIODevice::WriteOnly);

    if (response->getResponseCode() > 0)
    {
        outData << books.size();

        for (int i = 0; i < books.size(); ++i)
        {
            outData << *books.at(i);
            outData << (qint8) 0;
        }
    }

    response->setData(responseDataBytes);

    qDeleteAll(books.begin(), books.end());
    books.clear();

    emit result(response->getResponseCode(), response);
}


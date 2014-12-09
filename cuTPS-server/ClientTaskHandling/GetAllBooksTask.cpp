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
    //TODO: use the result of getAllTextbooks and probably need to remove the two appends below
    ServerResponse getBooks = server->getAllTextbooks(sessionId, books);
    books.append(Textbook(13, "Everything I Want To Do Is Illegal", "1st", "me", 999, true, "123123123123"));
    books.append(Textbook(666, "The Zen of Farting", "10th", "george lucas", 1, true, "321321321321"));

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    //response->setResponseCode(getBooks.code == Fail ? 0x0 : 0x1);
    response->setResponseCode(0x1); // TODO: remove this
    response->setSessionId(sessionId);

    QByteArray responseDataBytes;
    QDataStream outData(&responseDataBytes, QIODevice::WriteOnly);

    // if (getBooks.code == Success)
    if (true) // TODO: remove this
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


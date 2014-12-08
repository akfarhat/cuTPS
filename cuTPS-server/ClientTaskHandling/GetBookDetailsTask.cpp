#include "GetBookDetailsTask.h"

#include <QDebug>

GetBookDetailsTask::GetBookDetailsTask(Server* srv)
    : WorkerTask(srv)
{
}

void GetBookDetailsTask::run()
{
    qDebug() << "Get book details task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request->getRequestId();

    qint32 numBooks;
    bool pass = true;
    QDataStream in(request->getData(), QIODevice::ReadOnly);

    in >> numBooks;

    QVector<Textbook*> results;
    for (int i = 0; i < numBooks; ++i)
    {
        qint32 bookId;
        in >> bookId;
        Textbook* tPtr;
        ServerResponse r = server->getTextbookDetails(sessionId,
                                                      static_cast<int>(bookId),
                                                      &tPtr);
        results.append(tPtr);
        if (r.code == Fail) pass = false;
    }

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    response->setResponseCode(pass ? 0x1 : 0x0);
    response->setSessionId(sessionId);

    QByteArray responseDataBytes;
    QDataStream outData(&responseDataBytes, QIODevice::WriteOnly);

    if (pass)
    {
        numBooks = static_cast<qint32>(results.size());
        outData << numBooks;
        for (int i = 0; i < numBooks; ++i)
        {
            outData << *results.at(i);
        }

        response->setData(responseDataBytes);
    } else {
        outData << (qint32)0;
    }

    emit result(response->getResponseCode(), response);
}


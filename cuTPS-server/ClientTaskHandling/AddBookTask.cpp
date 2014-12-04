#include "AddBookTask.h"

#include <QDebug>

AddBookTask::AddBookTask(Server* srv)
    : WorkerTask(srv)
{
}

void AddBookTask::run()
{
    qDebug() << "Add book task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request->getRequestId();

    Textbook book;
    QDataStream in(request->getData(), QIODevice::ReadOnly);

    in >> book;

    qDebug() << "TPSAddBookTask Deserialized textbook: ";
    qDebug() << " id = " << QString::number(book.getId());
    qDebug() << " ISBN = " << book.getISBN();
    qDebug() << " name = " << book.getName();
    qDebug() << " price = " << QString::number(book.getPriceCents());
    qDebug() << "available? = " << book.getAvailability();

    ServerResponse r = server->addTextbook(sessionId, book);

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    response->setResponseCode(r.code == Fail ? 0x0 : 0x1);
    response->setSessionId(sessionId);

    emit result(response->getResponseCode(), response);
}


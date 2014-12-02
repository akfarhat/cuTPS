#include "AddBookTask.h"
#include "TPSNetUtils.h"

#include <QDebug>

AddBookTask::AddBookTask(Server* srv)
    : WorkerTask(srv)
{
}

void AddBookTask::run()
{
    qDebug() << "Add book task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request.requestId;

    Textbook book;

    QDataStream in(iblock, QIODevice::ReadOnly);
    TPSNetUtils::DeserializeTextbook(&book, &in);

    qDebug() << "TPSAddBookTask Deserialized textbook: ";
    qDebug() << " id = " << QString::number(book.getId());
    qDebug() << " ISBN = " << book.getISBN();
    qDebug() << " name = " << book.getName();
    qDebug() << " price = " << QString::number(book.getPriceCents());
    qDebug() << "available? = " << book.getAvailability();

    ServerResponse r = server->addTextbook(sessionId, book);

    TPSNetProtocol::NetResponse response;
    QByteArray data;
    QDataStream out(oblock, QIODevice::WriteOnly);

    setupResponse(response,
                  r.code == Fail ? 0x0 : 0x1,
                  &data,
                  &out);

    emit result(response.responseCode, oblock);
}


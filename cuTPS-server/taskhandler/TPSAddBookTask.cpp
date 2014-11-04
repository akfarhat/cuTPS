#include "TPSAddBookTask.h"

#include <QDebug>

TPSAddBookTask::TPSAddBookTask(Server* srv)
    : TPSWorkerTask(srv)
{
}

void TPSAddBookTask::run()
{
    qDebug() << "Add book task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request.requestId;

    Textbook book;

    QDataStream in(iblock, QIODevice::ReadOnly);
    parseTextbook(&book, &in);

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

void TPSAddBookTask::parseTextbook(Textbook*, QDataStream*)
{

}


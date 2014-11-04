#include "TPSGetBookDetailsTask.h"

#include <QDebug>

TPSGetBookDetailsTask::TPSGetBookDetailsTask(Server* srv)
    : TPSWorkerTask(srv)
{
}

void TPSGetBookDetailsTask::run()
{
    qDebug() << "Get book details task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request.requestId;

    int bookId = -1;

    QDataStream in(iblock, QIODevice::ReadOnly);
    in >> bookId;

    ServerResponse r = server->getTextbookDetails(sessionId, bookId);

    // how to get actual details?

    TPSNetProtocol::NetResponse response;
//    QByteArray data;
//    QDataStream out(oblock, QIODevice::WriteOnly);

//    setupResponse(response,
//                  r.code == Fail ? 0x0 : 0x1,
//                  &data,
//                  &out);

    emit result(response.responseCode, oblock);
}


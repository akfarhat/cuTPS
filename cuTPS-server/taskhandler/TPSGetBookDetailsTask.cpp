#include "TPSGetBookDetailsTask.h"
#include "TPSNetUtils.h"

#include <QDebug>

TPSGetBookDetailsTask::TPSGetBookDetailsTask(ServerAPI* srv)
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

    qDebug() << "Read in bookID = " << bookId;

    //std::unique_ptr<Textbook>* ppText;
    Textbook *returnBook = NULL;
    ServerResponse r = server->getTextbookDetails(sessionId, bookId, &returnBook);

    TPSNetProtocol::NetResponse response;
    QByteArray data;
    QDataStream out(oblock, QIODevice::WriteOnly);
    QDataStream outData(&data, QIODevice::WriteOnly);

    TPSNetUtils::SerializeTextbook(&outData, returnBook);

    qDebug() << "Get book details setup the response";

    setupResponse(response,
                  r.code == Fail ? 0x0 : 0x1,
                  &data,
                  &out);

    qDebug() << "Get book details, notify done";

    emit result(response.responseCode, oblock);
}


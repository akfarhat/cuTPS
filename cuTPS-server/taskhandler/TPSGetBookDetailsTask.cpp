#include "TPSGetBookDetailsTask.h"
#include "TPSNetUtils.h"

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

    std::unique_ptr<Textbook>* ppText;
    ServerResponse r = server->getTextbookDetails(sessionId, bookId, ppText);

    TPSNetProtocol::NetResponse response;
    QByteArray data;
    QDataStream out(oblock, QIODevice::WriteOnly);

    TPSNetUtils::SerializeTextbook(&out, *ppText);

    setupResponse(response,
                  r.code == Fail ? 0x0 : 0x1,
                  &data,
                  &out);

    emit result(response.responseCode, oblock);
}


#include "TPSGetRequiredBooksTask.h"

#include <QDebug>

TPSGetRequiredBooksTask::TPSGetRequiredBooksTask(Server* srv)
    : TPSWorkerTask(srv)
{
}

void TPSGetRequiredBooksTask::run()
{
    qDebug() << "GetRequiredBooks task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request.requestId;

    QString username;

    QDataStream in(iblock, QIODevice::ReadOnly);
    in >> username;

    QVector<int>* ids = new QVector<int>();

    qDebug() << "calling the getRequiredTextbooks API for user " << username;

    ServerResponse r = server->getRequiredTextbooks(sessionId, username, ids);

    TPSNetProtocol::NetResponse response;
    QByteArray data;
    QDataStream out(oblock, QIODevice::WriteOnly);

    qDebug() << "writing " << ids->size() << " book ids to outgoing buffer...";

    for (int i = 0; i < ids->size(); ++i)
    {
        out << ((qint32) ids->at(i));
    }

    qDebug() << "formulating server response... ";

    setupResponse(response,
                  r.code == Fail ? 0x0 : 0x1,
                  &data,
                  &out);

    qDebug() << "Result of getRequiredBooks: " << r.code << "\n";

    emit result(response.responseCode, oblock);
}


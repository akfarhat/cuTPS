#include "AddItemTask.h"

#include <QDebug>

#include "Defines.h"

using namespace TPSNetProtocolDef;

AddItemTask::AddItemTask(Server* srv)
    : WorkerTask(srv)
{
}

void AddItemTask::run()
{
    qDebug() << "Add item task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request->getRequestId();

    QDataStream in(request->getData(), QIODevice::ReadOnly);
    ServerResponse r;
    qint32 itemId = -1;

    // TODO: make server return ids for created items
    switch (request->getInvocation())
    {

    case IAddBook:
    {
        Textbook text;
        in >> text;
        r = server->addTextbook(sessionId, text);
        // set itemid
    }

    case IAddChapter:
    {
        Chapter ch;
        qint32 textId;

        in >> textId >> ch;

        ch.setParentTextbookId(textId);
        r = server->addChapter(sessionId, ch);
        // set itemId
    }

    case IAddSection:
    {
        Section s;
        qint32 textId, chId;

        in >> textId >> chId >> s;

        s.setParentChapterId(chId);
        s.setParentTextbookId(textId);
        r = server->addSection(sessionId, s);
        // set Itemid
    }

    }

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    response->setResponseCode(r.code == Fail ? 0x0 : 0x1);
    response->setSessionId(sessionId);

    QByteArray responseDataBytes;
    QDataStream outData(&responseDataBytes, QIODevice::WriteOnly);
    outData << itemId;
    response->setData(responseDataBytes);

    emit result(response->getResponseCode(), response);
}


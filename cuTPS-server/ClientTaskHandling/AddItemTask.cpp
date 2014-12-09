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

    switch (request->getInvocation())
    {

    case IAddBook:
    {
        Textbook text;
        in >> text;
        itemId = text.getId();

        if (itemId < 0) {
            // Add a new textbook
            r = server->addTextbook(sessionId, text, itemId);
        } else {
            // Replace an existing one
            r = server->replaceTextbook(sessionId, itemId, text);
        }
    }

    case IAddChapter:
    {
        Chapter ch;
        qint32 textId;
        in >> textId >> ch;
        ch.setParentTextbookId(textId);
        itemId = ch.getId();

        if (itemId < 0) {
            r = server->addChapter(sessionId, ch, itemId);
        } else {
            r = server->replaceChapter(sessionId, itemId, ch);
        }
    }

    case IAddSection:
    {
        Section s;
        qint32 textId, chId;
        in >> textId >> chId >> s;
        s.setParentChapterId(chId);
        s.setParentTextbookId(textId);
        itemId = s.getId();

        if (itemId < 0) {
            r = server->addSection(sessionId, s, itemId);
        } else {
            r = server->replaceSection(sessionId, itemId, s);
        }
    }

    default:
        r.code = Fail;
    }

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    response->setResponseCode(r.code == Fail ? 0x0 : 0x1);
    response->setSessionId(sessionId);

    if (response->getResponseCode() > 0)
    {
        QByteArray responseDataBytes;
        QDataStream outData(&responseDataBytes, QIODevice::WriteOnly);
        outData << itemId;
        response->setData(responseDataBytes);
    }

    emit result(response->getResponseCode(), response);
}


#include "GetRequiredBooksTask.h"

#include <QDebug>
#include <QUuid>
#include <QByteArray>
#include <QDataStream>

#include "Entity/NetResponse.h"
#include "Entity/Course.h"
#include "Entity/Textbook.h"

GetRequiredBooksTask::GetRequiredBooksTask(Server* srv)
    : WorkerTask(srv)
{
}

void GetRequiredBooksTask::run()
{
    qDebug() << "GetRequiredBooks task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request->getRequestId();

    QDataStream in(request->getData(), QIODevice::ReadOnly);

    // TODO: get list of actual user's courses
    QVector<Course> courses;
    Course c;
    c.setId(42);
    c.addRequiredTextId(1);
    c.addRequiredTextId(2);
    courses.append(c);

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    //response->setResponseCode(getBooks.code == Fail ? 0x0 : 0x1);
    response->setResponseCode(0x1);
    response->setSessionId(sessionId);

    QByteArray responseDataBytes;
    QDataStream outData(&responseDataBytes, QIODevice::WriteOnly);

    if (response->getResponseCode() > 0)
    {
        // |numcourses|(|course||numbooks||..books..|)(|course||numbooks|...
        outData << static_cast<qint32>(courses.size());

        for (Course course : courses)
        {
            outData << course;
            outData << static_cast<qint32>(course.getRequiredTextIds().size());

            for (qint32 textId : course.getRequiredTextIds())
            {
                Textbook* tPtr;
                ServerResponse r = server->getTextbookDetails(sessionId, textId, &tPtr);
                outData << *tPtr;
                delete tPtr;
            }
        }

        response->setData(responseDataBytes);
    }

    emit result(response->getResponseCode(), response);
}


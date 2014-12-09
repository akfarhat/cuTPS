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

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    response->setSessionId(sessionId);
    ServerResponse r;
    QVector<Course> courses;
    int sessionUserId;

    r = server->getSessionUserId(sessionId, sessionUserId);

    if (r.code == Fail)
    {
        emit result(response->getResponseCode(), response);
        return;
    } else {
        response->setResponseCode(1);
    }

    r = server->getStudentCourses(sessionId, sessionUserId, courses);


    QByteArray responseDataBytes;
    QDataStream outData(&responseDataBytes, QIODevice::WriteOnly);

    if (courses.size() > 0)
    {
        // Format:
        // |numcourses=n|(|course||numbooks||..books..|)(|course||numbooks|...books..|)..n

        outData << static_cast<qint32>(courses.size());

        for (Course course : courses)
        {
            outData << course;
            outData << static_cast<qint32>(course.getRequiredTextIds().size());

            for (qint32 textId : course.getRequiredTextIds())
            {
                Textbook* tPtr;
                r = server->getTextbookDetails(sessionId, textId, &tPtr);
                outData << *tPtr;
                delete tPtr;
            }
        }

        response->setData(responseDataBytes);
    }

    emit result(response->getResponseCode(), response);
}


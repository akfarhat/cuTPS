#include "AddUserTask.h"

#include <QDebug>
#include <QUuid>
#include <QByteArray>
#include <QDataStream>

#include "Entity/NetResponse.h"
#include "Entity/Student.h"

AddUserTask::AddUserTask(Server* srv)
    : WorkerTask(srv)
{
}

void AddUserTask::run()
{
    qDebug() << "AddUserTask task was run";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request->getRequestId();

    QDataStream in(request->getData(), QIODevice::ReadOnly);
    Student usr;
    QString pwd;
    qint32 usrId;

    in >> usr >> pwd;

    ServerResponse r = server->registerStudentUser(sessionId, usr, pwd, &usrId);

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    response->setResponseCode(r.code == Fail ? 0x0 : 0x1);
    response->setSessionId(sessionId);

    if (response->getResponseCode() > 0)
    {
        QByteArray responseDataBytes;
        QDataStream outData(&responseDataBytes, QIODevice::WriteOnly);
        outData << usrId;
        response->setData(responseDataBytes);
    }

    emit result(response->getResponseCode(), response);
}

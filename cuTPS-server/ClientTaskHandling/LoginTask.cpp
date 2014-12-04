#include "LoginTask.h"

#include <QDebug>
#include <QString>

LoginTask::LoginTask(Server* srv)
    : WorkerTask(srv)
{
}

void LoginTask::run()
{
    qDebug() << "Login task ruN!";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request->getRequestId();

    UserCredentials credentials;

    QDataStream in(request->getData(), QIODevice::ReadOnly);

    in >> credentials.username >> credentials.password;

    qDebug() << credentials.username << credentials.password;

    ServerResponse r = server->authenticateUser(sessionId, credentials);

    if (r.code == Fail)
    {
        qDebug() << "Failed login attempt login/pwd: ";
    }
    else
    {
        qDebug() << "Successful login! >";
    }

    NetResponse* response = new NetResponse();
    response->setInvocation(request->getInvocation());
    response->setRequestId(request->getRequestId());
    response->setResponseCode(r.code == Fail ? 0x0 : 0x1);
    response->setSessionId(sessionId);

    emit result(response->getResponseCode(), response);
}

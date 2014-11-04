#include "TPSLoginTask.h"

#include <QDebug>
#include <QString>

TPSLoginTask::TPSLoginTask(Server* srv)
    : TPSWorkerTask(srv)
{
}

void TPSLoginTask::run()
{
    qDebug() << "Login task ruN!";
    qDebug() << "Doing job for session: " << sessionId
             << "Request: " << request.requestId;

    UserCredentials credentials;

    QDataStream in(iblock, QIODevice::ReadOnly);
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

    qDebug() << credentials.username << " " << credentials.password;

    TPSNetProtocol::NetResponse response;

    response.invocation = request.invocation;
    response.requestId = request.requestId;
    response.sessionId = sessionId;
    r.code == Fail ? response.responseCode = 0x0 : response.responseCode = 0x1;

    QByteArray data;
    response.data = &data;

    QDataStream out(oblock, QIODevice::WriteOnly);
    TPSNetUtils::SerializeResponse(&out, &response);

    emit result(response.responseCode, oblock);
}

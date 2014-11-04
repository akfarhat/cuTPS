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
    QByteArray data;
    QDataStream out(oblock, QIODevice::WriteOnly);

    setupResponse(response,
                  r.code == Fail ? 0x0 : 0x1,
                  &data,
                  &out);

    emit result(response.responseCode, oblock);
}

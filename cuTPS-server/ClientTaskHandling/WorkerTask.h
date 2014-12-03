// Class: TPSWorkerTask
// Type: Control
// Description:
//     Represents a job instance for a request made
//     to the server. This object is given a separate
//     thread on which to perform its jon in a non-blocking manner.
//
//     Upon completion of the job, a signal will be emitted and
//     handled by the TPSClient that instantiated this object


#ifndef WORKERTASK_H
#define WORKERTASK_H

#include <QRunnable>
#include <QObject> // for singals+slots
#include <QUuid>
#include <QDebug>
#include <QTcpSocket>
#include <QDataStream>
#include <QByteArray>

#include <ServerNetworking/NetClient.h>
#include <Entity/NetRequest.h>
#include <Entity/NetResponse.h>
#include "Defines.h"
#include "Server.h"

class WorkerTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    WorkerTask(Server* srv);

    void setSessionId(QUuid sessionId);
    void setRequest(NetRequest* request);

signals:
    // emmit an event signaling the completion of the task.
    // Params:
    //     code (int): a task-specific status indicator
    void result(int code, QByteArray* response);

protected:
    // The thread method in which to perform this task
    virtual void run() = 0;

    // Reference to the server API for updating the system
    // model with each request
    Server *server;

    NetRequest* request;
    QUuid sessionId;
};

#endif // WORKERTASK_H

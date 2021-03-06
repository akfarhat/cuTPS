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

#include "Server.h"
#include <Entity/NetRequest.h>
#include <Entity/NetResponse.h>

class WorkerTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    WorkerTask(Server* srv);
    virtual ~WorkerTask();
    void setSessionId(QUuid sessionId);
    void setRequest(NetRequest* request);

signals:
    // emmit an event signaling the completion of the task.
    // Params:
    //     code (int): a task-specific status indicator
    void result(int code, NetResponse* response);

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

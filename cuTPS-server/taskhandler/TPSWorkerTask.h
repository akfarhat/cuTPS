// Class: TPSWorkerTask
// Type: Control
// Description:
//     Represents a job instance for a request made
//     to the server. This object is given a separate
//     thread on which to perform its jon in a non-blocking manner.
//
//     Upon completion of the job, a signal will be emitted and
//     handled by the TPSClient that instantiated this object


#ifndef TPSWORKERTASK_H
#define TPSWORKERTASK_H

#include <QRunnable>
#include <QObject> // for singals+slots
#include <QUuid>
#include <QDebug>
#include <QTcpSocket>
#include <QDataStream>
#include <QByteArray>

#include "Defines.h"
#include "TPSClient.h"
#include "Server.h"

class TPSWorkerTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    TPSWorkerTask(Server* srv);

    void setSessionId(QUuid sessionId);
    void setRequest(TPSNetProtocol::NetRequest& request);
    void setInputDataBlock(QByteArray* idata);
    void setResponseDataBlock(QByteArray* odata);

signals:
    // emmit an event signaling the completion of the task.
    // Params:
    //     code (int): a task-specific status indicator
    void result(int code, QByteArray* response);

protected:
    // The thread method in which to perform this task
    virtual void run() = 0;
    void setupResponse(TPSNetProtocol::NetResponse& response,
                       qint8 code,
                       QByteArray* dataBlock,
                       QDataStream* outStream);

    // Reference to the server API for updating the system
    // model with each request
    Server *server;

    // The request identifier
    TPSNetProtocol::NetRequest request;
    QUuid sessionId;
    QByteArray *iblock;
    QByteArray *oblock;
};

#endif // TPSWORKERTASK_H

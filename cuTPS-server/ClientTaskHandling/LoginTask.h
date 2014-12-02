#ifndef LOGINTASK_H
#define LOGINTASK_H

#include <QUuid>
#include <QDataStream>

#include "WorkerTask.h"
#include "Server.h"

// TASK DATA FORMAT: |-- username --|-- password --|

class LoginTask : public WorkerTask
{
public:
    LoginTask(Server* srv);
    virtual void run();
};

#endif // LOGINTASK_H

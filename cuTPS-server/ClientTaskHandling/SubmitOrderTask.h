#ifndef SUBMITORDERTASK_H
#define SUBMITORDERTASK_H

#include <QUuid>
#include <QDataStream>

#include "WorkerTask.h"
#include "Server.h"

// TASK DATA FORMAT: |-- username --|-- password --|

class SubmitOrderTask : public WorkerTask
{
public:
    SubmitOrderTask(Server* srv);
    virtual void run();
};


#endif // SUBMITORDERTASK_H

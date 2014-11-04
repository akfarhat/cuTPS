#ifndef TPSSUBMITORDERTASK_H
#define TPSSUBMITORDERTASK_H

#include <QUuid>
#include <QDataStream>

#include "TPSWorkerTask.h"
#include "Server.h"

// TASK DATA FORMAT: |-- username --|-- password --|

class TPSSubmitOrderTask : public TPSWorkerTask
{
public:
    TPSSubmitOrderTask(Server* srv);
    virtual void run();
};


#endif // TPSSUBMITORDERTASK_H

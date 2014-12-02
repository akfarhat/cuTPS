#ifndef TPSSUBMITORDERTASK_H
#define TPSSUBMITORDERTASK_H

#include <QUuid>
#include <QDataStream>

#include "TPSWorkerTask.h"
#include "TPSNetUtils.h"
#include "Server.h"

// TASK DATA FORMAT: |-- username --|-- password --|

class TPSSubmitOrderTask : public TPSWorkerTask
{
public:
    TPSSubmitOrderTask(ServerAPI* srv);
    virtual void run();
};


#endif // TPSSUBMITORDERTASK_H

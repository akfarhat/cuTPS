#ifndef TPSLOGINTASK_H
#define TPSLOGINTASK_H

#include <QUuid>
#include <QDataStream>

#include "TPSWorkerTask.h"
#include "Server.h"

// TASK DATA FORMAT: |-- username --|-- password --|

class TPSLoginTask : public TPSWorkerTask
{
public:
    TPSLoginTask(Server* srv);
    virtual void run();
};

#endif // TPSLOGINTASK_H

#ifndef TPSGETREQUIREDBOOKSTASK_H
#define TPSGETREQUIREDBOOKSTASK_H

#include <QUuid>
#include <QDataStream>

#include "TPSWorkerTask.h"
#include "Server.h"

// TASK DATA FORMAT: |-- username --|-- password --|

class TPSGetRequiredBooksTask : public TPSWorkerTask
{
public:
    TPSGetRequiredBooksTask(Server* srv);
    virtual void run();
};


#endif // TPSGETREQUIREDBOOKSTASK_H

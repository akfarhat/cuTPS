#ifndef TPSGETBOOKDETAILSTASK_H
#define TPSGETBOOKDETAILSTASK_H

#include <QUuid>
#include <QDataStream>

#include "TPSWorkerTask.h"
#include "Server.h"

// TASK DATA FORMAT: |-- username --|-- password --|

class TPSGetBookDetailsTask : public TPSWorkerTask
{
public:
    TPSGetBookDetailsTask(ServerAPI* srv);
    virtual void run();
};


#endif // TPSGETBOOKDETAILSTASK_H

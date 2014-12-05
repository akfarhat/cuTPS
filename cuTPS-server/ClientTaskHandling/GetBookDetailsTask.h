#ifndef GETBOOKDETAILSTASK_H
#define GETBOOKDETAILSTASK_H

#include <QUuid>
#include <QDataStream>

#include "WorkerTask.h"
#include "Server.h"

// TASK DATA FORMAT: |-- username --|-- password --|

class GetBookDetailsTask : public WorkerTask
{
public:
    GetBookDetailsTask(Server* srv);
    virtual void run();
};


#endif // GETBOOKDETAILSTASK_H

#ifndef GETREQUIREDBOOKSTASK_H
#define GETREQUIREDBOOKSTASK_H

#include <QUuid>
#include <QDataStream>

#include "WorkerTask.h"
#include "Server.h"

// TASK DATA FORMAT: |-- username --|-- password --|

class GetRequiredBooksTask : public WorkerTask
{
public:
    GetRequiredBooksTask(Server* srv);
    virtual void run();
};


#endif // GETREQUIREDBOOKSTASK_H

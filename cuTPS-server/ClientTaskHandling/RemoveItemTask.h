#ifndef REMOVEITEMTASK_H
#define REMOVEITEMTASK_H

#include "WorkerTask.h"
#include "Server.h"

class RemoveItemTask : public WorkerTask
{
public:
    RemoveItemTask(Server* srv);
    virtual void run();
};

#endif // REMOVEITEMTASK_H

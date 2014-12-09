#ifndef ADDUSERTASK_H
#define ADDUSERTASK_H

#include "WorkerTask.h"
#include "Server.h"

class AddUserTask : public WorkerTask
{
public:
    AddUserTask(Server* srv);
    virtual void run();
};

#endif // ADDUSERTASK_H

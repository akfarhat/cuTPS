#ifndef REMOVECOURSETASK_H
#define REMOVECOURSETASK_H

#include "WorkerTask.h"
#include "Server.h"

class RemoveCourseTask : public WorkerTask
{
public:
    RemoveCourseTask(Server* srv);
    virtual void run();
};

#endif // REMOVECOURSETASK_H

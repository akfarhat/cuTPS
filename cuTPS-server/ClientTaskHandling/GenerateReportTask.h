#ifndef GENERATEREPORTTASK_H
#define GENERATEREPORTTASK_H

#include "WorkerTask.h"

class GenerateReportTask : public WorkerTask
{
public:
    GenerateReportTask(Server* srv);
    virtual void run();
};

#endif // GENERATEREPORTTASK_H

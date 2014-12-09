#ifndef SUTASKFACTORY_H
#define SUTASKFACTORY_H

#include "TaskAbsFactory.h"
#include "WorkerTask.h"
#include "Defines.h"

class SUTaskFactory : public TaskAbsFactory
{
public:
    SUTaskFactory();
    virtual ~SUTaskFactory();
    virtual WorkerTask* createTask(
            Server *srvInst,
            TPSNetProtocolDef::InvocationDescriptor invoc);
};

#endif // SUTASKFACTORY_H

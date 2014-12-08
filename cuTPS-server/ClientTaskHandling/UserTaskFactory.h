#ifndef USERTASKFACTORY_H
#define USERTASKFACTORY_H

#include "TaskAbsFactory.h"
#include "WorkerTask.h"
#include "Defines.h"

class UserTaskFactory : public TaskAbsFactory
{
public:
    UserTaskFactory();

    virtual WorkerTask* createTask(
            Server *srvInst,
            TPSNetProtocolDefs::InvocationDescriptor invoc);
};

#endif // USERTASKFACTORY_H

#ifndef ADMINTASKFACTORY_H
#define ADMINTASKFACTORY_H

#include "TaskAbsFactory.h"
#include "WorkerTask.h"
#include "Defines.h"

class AdminTaskFactory : public TaskAbsFactory
{
public:
    AdminTaskFactory();

    virtual WorkerTask* createTask(
            Server *srvInst,
            TPSNetProtocolDefs::InvocationDescriptor invoc);

};

#endif // ADMINTASKFACTORY_H

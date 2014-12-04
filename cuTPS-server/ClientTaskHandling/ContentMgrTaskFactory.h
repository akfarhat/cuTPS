#ifndef CONTENTMGRTASKFACTORY_H
#define CONTENTMGRTASKFACTORY_H

#include "TaskAbsFactory.h"
#include "WorkerTask.h"
#include "Defines.h"

class ContentMgrTaskFactory : public TaskAbsFactory
{
public:
    ContentMgrTaskFactory();

    virtual WorkerTask* createTask(
            Server *srvInst,
            TPSNetProtocolDefs::InvocationDescriptor invoc);
};

#endif // CONTENTMGRTASKFACTORY_H

#ifndef LOGINTASKFACTORY_H
#define LOGINTASKFACTORY_H

#include "TaskAbsFactory.h"
#include "WorkerTask.h"
#include "Defines.h"

class LoginTaskFactory : public TaskAbsFactory
{
public:
    LoginTaskFactory();
    virtual ~LoginTaskFactory();
    virtual WorkerTask* createTask(
            Server *srvInst,
            TPSNetProtocolDef::InvocationDescriptor invoc);

};

#endif // LOGINTASKFACTORY_H

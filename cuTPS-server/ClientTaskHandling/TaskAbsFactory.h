#ifndef TASKABSFACTORY_H
#define TASKABSFACTORY_H

#include <exception>

#include "Defines.h"
#include "./WorkerTask.h"
#include "Server.h"

class TaskAbsFactory
{
public:
    TaskAbsFactory();
    virtual ~TaskAbsFactory();
    virtual WorkerTask* createTask(Server* srvInst,
                           TPSNetProtocolDefs::InvocationDescriptor invoc) = 0;

    class PermissionDeniedExc : std::exception
    {
    public:
        virtual const char* what() const throw()
        {
          return "Attempt to run an unathorized task, finished with client";
        }
    };
};

#endif // TASKABSFACTORY_H

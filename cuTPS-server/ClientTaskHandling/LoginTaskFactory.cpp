#include "LoginTaskFactory.h"
#include "LoginTask.h"

using namespace TPSNetProtocolDef;

LoginTaskFactory::LoginTaskFactory()
{}

LoginTaskFactory::~LoginTaskFactory()
{}

WorkerTask* LoginTaskFactory::createTask(
        Server *srvInst,
        TPSNetProtocolDef::InvocationDescriptor invoc)
{
    switch (invoc)
    {

    case ILogin: {
        return new LoginTask(srvInst);
    }

    default: {
        throw PermissionDeniedExc();
    }

    }
}

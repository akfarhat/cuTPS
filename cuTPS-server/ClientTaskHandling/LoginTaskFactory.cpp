#include "LoginTaskFactory.h"
#include "LoginTask.h"

using namespace TPSNetProtocolDefs;

LoginTaskFactory::LoginTaskFactory()
{}

LoginTaskFactory::~LoginTaskFactory()
{}

WorkerTask* LoginTaskFactory::createTask(
        Server *srvInst,
        TPSNetProtocolDefs::InvocationDescriptor invoc)
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

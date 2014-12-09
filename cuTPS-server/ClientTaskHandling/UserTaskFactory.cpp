#include "UserTaskFactory.h"
#include "GetBookDetailsTask.h"
#include "GetRequiredBooksTask.h"
#include "SubmitOrderTask.h"

using namespace TPSNetProtocolDef;

UserTaskFactory::UserTaskFactory()
{
}

WorkerTask* UserTaskFactory::createTask(
        Server *srvInst,
        TPSNetProtocolDef::InvocationDescriptor invoc)
{
    switch (invoc)
    {

    case IGetBookDetails: {
        return new GetBookDetailsTask(srvInst);
        break;
    }

    case IGetRequiredBooks: {
        return new GetRequiredBooksTask(srvInst);
        break;
    }

    case ISubmitOrder: {
        return new SubmitOrderTask(srvInst);
        break;
    }

    default: {
        throw PermissionDeniedExc();
        break;
    }

    }
}

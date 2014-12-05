#include "UserTaskFactory.h"
#include "GetBookDetailsTask.h"
#include "GetRequiredBooksTask.h"
#include "SubmitOrderTask.h"

using namespace TPSNetProtocolDefs;

UserTaskFactory::UserTaskFactory()
{
}

WorkerTask* UserTaskFactory::createTask(
        Server *srvInst,
        TPSNetProtocolDefs::InvocationDescriptor invoc)
{
    switch (invoc)
    {

    case IGetBookDetails: {
        return new GetBookDetailsTask(srvInst);
    }

    case IGetRequiredBooks: {
        return new GetRequiredBooksTask(srvInst);
    }

    case ISubmitOrder: {
        return new SubmitOrderTask(srvInst);
    }

    default: {
        throw PermissionDeniedExc();
    }

    }
}

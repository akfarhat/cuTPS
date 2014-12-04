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

    case GetBookDetails: {
        return new GetBookDetailsTask(srvInst);
    }

    case GetRequiredBooks: {
        return new GetRequiredBooksTask(srvInst);
    }

    case SubmitOrder: {
        return new SubmitOrderTask(srvInst);
    }

    default: {
        throw PermissionDeniedExc();
    }

    }
}

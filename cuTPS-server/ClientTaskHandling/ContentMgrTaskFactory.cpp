#include "ContentMgrTaskFactory.h"
#include "AddBookTask.h"
#include "AddCourseTask.h"
#include "GetBookDetailsTask.h"

using namespace TPSNetProtocolDefs;

ContentMgrTaskFactory::ContentMgrTaskFactory()
{
}

WorkerTask* ContentMgrTaskFactory::createTask(
        Server *srvInst,
        TPSNetProtocolDefs::InvocationDescriptor invoc)
{
    switch (invoc)
    {

    case IAddBook: {
        return new AddBookTask(srvInst);
    }

    case IAddCourse: {
        return new AddCourseTask(srvInst);
    }

    case IGetBookDetails: {
        return new GetBookDetailsTask(srvInst);
    }

    default: {
        throw PermissionDeniedExc();
    }

    }
}

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

    case AddBook: {
        return new AddBookTask(srvInst);
    }

    case AddCourse: {
        return new AddCourseTask(srvInst);
    }

    case GetBookDetails: {
        return new GetBookDetailsTask(srvInst);
    }

    default: {
        throw PermissionDeniedExc();
    }

    }
}

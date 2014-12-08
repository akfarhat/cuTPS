#include "ContentMgrTaskFactory.h"
#include "AddItemTask.h"
#include "AddCourseTask.h"
#include "GetBookDetailsTask.h"
#include "GetAllBooksTask.h"
#include "GetAllCoursesTask.h"
#include "RmItemTask.h"

using namespace TPSNetProtocolDef;

ContentMgrTaskFactory::ContentMgrTaskFactory()
{
}

WorkerTask* ContentMgrTaskFactory::createTask(
        Server *srvInst,
        TPSNetProtocolDef::InvocationDescriptor invoc)
{
    switch (invoc)
    {

    case IAddChapter:
    case IAddSection:
    case IAddBook: {
        return new AddItemTask(srvInst);
    }

    case IAddCourse: {
        return new AddCourseTask(srvInst);
    }

    case IGetBookDetails: {
        return new GetBookDetailsTask(srvInst);
    }

    case IGetAllBooks: {
        return new GetAllBooksTask(srvInst);
    }

    case IGetAllCourses: {
        return new GetAllCoursesTask(srvInst);
    }

    case IRmBook:
    case IRmChapter:
    case IRmSection: {
        return new RemoveItemTask(srvInst);
    }

    default: {
        throw PermissionDeniedExc();
    }

    }
}

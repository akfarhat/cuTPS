#include "ContentMgrTaskFactory.h"
#include "AddItemTask.h"
#include "AddCourseTask.h"
#include "GetBookDetailsTask.h"
#include "GetAllBooksTask.h"
#include "GetAllCoursesTask.h"
#include "RemoveItemTask.h"
#include "RemoveCourseTask.h"
#include "BookLinkTask.h"

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
    case IAddBook:
    {
        return new AddItemTask(srvInst);
        break;
    }

    case IAddCourse:
    {
        return new AddCourseTask(srvInst);
        break;
    }

    case IGetBookDetails:
    {
        return new GetBookDetailsTask(srvInst);
        break;
    }

    case IGetAllBooks:
    {
        return new GetAllBooksTask(srvInst);
        break;
    }

    case IGetAllCourses:
    {
        return new GetAllCoursesTask(srvInst);
        break;
    }

    case IRmBook:
    case IRmChapter:
    case IRmSection:
    {
        return new RemoveItemTask(srvInst);
    }

    case IRmCourse:
    {
        return new RemoveCourseTask(srvInst);
    }

    case IBookLink:
    case IBookUnlink:
    {
        return new BookLinkTask(srvInst);
    }

    default: {
        throw PermissionDeniedExc();
    }

    }
}

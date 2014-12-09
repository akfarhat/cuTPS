#include "SUTaskFactory.h"
#include "LoginTask.h"
#include "AddItemTask.h"
#include "AddCourseTask.h"
#include "GetBookDetailsTask.h"
#include "GetRequiredBooksTask.h"
#include "SubmitOrderTask.h"
#include "GenerateReportTask.h"
#include "GetAllBooksTask.h"
#include "GetAllCoursesTask.h"
#include "AddUserTask.h"
#include "BanUserTask.h"
#include "RemoveItemTask.h"

using namespace TPSNetProtocolDef;

SUTaskFactory::SUTaskFactory()
{
}

SUTaskFactory::~SUTaskFactory()
{
}

WorkerTask* SUTaskFactory::createTask(
        Server *srvInst,
        TPSNetProtocolDef::InvocationDescriptor invoc)
{
    switch (invoc)
    {

    case ILogin: {
        return new LoginTask(srvInst);
    }

    case IAddChapter:
    case IAddSection:
    case IAddBook: {
        return new AddItemTask(srvInst);
    }

    case IAddUser: {
        return new AddUserTask(srvInst);
    }

    case IBanUser: {
        return new BanUserTask(srvInst);
    }

    case IAddCourse: {
        return new AddCourseTask(srvInst);
    }

    case IGetBookDetails: {
        return new GetBookDetailsTask(srvInst);
    }

    case IGetRequiredBooks: {
        return new GetRequiredBooksTask(srvInst);
    }

    case ISubmitOrder: {
        return new SubmitOrderTask(srvInst);
    }

    case IGenerateReport: {
        return new GenerateReportTask(srvInst);
    }

    case IGetAllBooks: {
        return new GetAllBooksTask(srvInst);
    }

    case IRmBook:
    case IRmChapter:
    case IRmSection: {
        return new RemoveItemTask(srvInst);
    }

    case IGetAllCourses: {
        return new GetAllCoursesTask(srvInst);
    }

    default: {
        throw PermissionDeniedExc();
    }

    }
}

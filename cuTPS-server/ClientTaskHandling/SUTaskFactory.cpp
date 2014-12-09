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
        break;
    }

    case IAddChapter:
    case IAddSection:
    case IAddBook: {
        return new AddItemTask(srvInst);
        break;
    }

    case IAddUser: {
        return new AddUserTask(srvInst);
        break;
    }

    case IBanUser: {
        return new BanUserTask(srvInst);
        break;
    }

    case IAddCourse: {
        return new AddCourseTask(srvInst);
        break;
    }

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

    case IGenerateReport: {
        return new GenerateReportTask(srvInst);
        break;
    }

    case IGetAllBooks: {
        return new GetAllBooksTask(srvInst);
        break;
    }

    case IRmBook:
    case IRmChapter:
    case IRmSection: {
        return new RemoveItemTask(srvInst);
        break;
    }

    case IGetAllCourses: {
        return new GetAllCoursesTask(srvInst);
        break;
    }

    default: {
        throw PermissionDeniedExc();
        break;
    }

    }
}

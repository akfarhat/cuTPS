#include "SUTaskFactory.h"
#include "LoginTask.h"
#include "AddBookTask.h"
#include "AddCourseTask.h"
#include "GetBookDetailsTask.h"
#include "GetRequiredBooksTask.h"
#include "SubmitOrderTask.h"
#include "GenerateReportTask.h"

using namespace TPSNetProtocolDefs;

SUTaskFactory::SUTaskFactory()
{
}

SUTaskFactory::~SUTaskFactory()
{
}

WorkerTask* SUTaskFactory::createTask(
        Server *srvInst,
        TPSNetProtocolDefs::InvocationDescriptor invoc)
{
    switch (invoc)
    {

    case ILogin: {
        return new LoginTask(srvInst);
    }

    case IAddBook: {
        return new AddBookTask(srvInst);
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

    default: {
        throw PermissionDeniedExc();
    }

    }
}

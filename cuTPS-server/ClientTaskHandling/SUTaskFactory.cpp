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

    case Login: {
        return new LoginTask(srvInst);
    }

    case AddBook: {
        return new AddBookTask(srvInst);
    }

    case AddCourse: {
        return new AddCourseTask(srvInst);
    }

    case GetBookDetails: {
        return new GetBookDetailsTask(srvInst);
    }

    case GetRequiredBooks: {
        return new GetRequiredBooksTask(srvInst);
    }

    case SubmitOrder: {
        return new SubmitOrderTask(srvInst);
    }

    case GenerateReport: {
        return new GenerateReportTask(srvInst);
    }

    default: {
        throw PermissionDeniedExc();
    }

    }
}

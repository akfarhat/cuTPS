#include "AdminTaskFactory.h"
#include "GenerateReportTask.h"
#include "AddUserTask.h"
#include "BanUserTask.h"

using namespace TPSNetProtocolDef;

AdminTaskFactory::AdminTaskFactory()
{
}

WorkerTask* AdminTaskFactory::createTask(
        Server *srvInst,
        TPSNetProtocolDef::InvocationDescriptor invoc)
{
    switch (invoc)
    {

    case IGenerateReport: {
        return new GenerateReportTask(srvInst);
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

    default: {
        throw PermissionDeniedExc();
        break;
    }

    }
}

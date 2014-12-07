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
    }

    case IAddUser: {
        return new AddUserTask(srvInst);
    }

    case IBanUser: {
        return new BanUserTask(srvInst);
    }

    default: {
        throw PermissionDeniedExc();
    }

    }
}

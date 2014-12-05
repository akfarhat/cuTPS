#include "AdminTaskFactory.h"
#include "GenerateReportTask.h"

using namespace TPSNetProtocolDefs;

AdminTaskFactory::AdminTaskFactory()
{
}

WorkerTask* AdminTaskFactory::createTask(
        Server *srvInst,
        TPSNetProtocolDefs::InvocationDescriptor invoc)
{
    switch (invoc)
    {

    case IGenerateReport: {
        return new GenerateReportTask(srvInst);
    }

    default: {
        throw PermissionDeniedExc();
    }

    }
}

#include <QTcpSocket>

#include "TPSWorkerTask.h"
#include "Defines.h"
#include "TPSClient.h"

TPSWorkerTask::TPSWorkerTask(Server *srv, QUuid session) {
    server = srv;
    sessionId = session;
}

void TPSWorkerTask::run()
{
    // .. do time consuming stuff
    emit result(666); // return result code that will be sent back to the client
}

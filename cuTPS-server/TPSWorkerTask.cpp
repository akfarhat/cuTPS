#include "TPSWorkerTask.h"

TPSWorkerTask::TPSWorkerTask()
{
}

void TPSWorkerTask::run()
{
    // Asynchronous code that is executed for each client connection

    qDebug() << "Task started";

    // ... do some stuff

    qDebug() << "Task done.";

    emit result(666); // return result code that will be sent back to the client
}

#include "TPSAddBookTask.h"

#include <QDebug>

TPSAddBookTask::TPSAddBookTask(Server* srv)
    : TPSWorkerTask(srv)
{
}

void TPSAddBookTask::run()
{
    qDebug() << "Add book task was run";
}


#ifndef TPSADDCOURSETASK_H
#define TPSADDCOURSETASK_H

#include <QUuid>
#include <QDataStream>

#include "TPSWorkerTask.h"
#include "Server.h"
#include "Entity/Course.h"

// TASK DATA FORMAT: |-- username --|-- password --|

class TPSAddCourseTask : public TPSWorkerTask
{
public:
    TPSAddCourseTask(Server* srv);
    virtual void run();

};


#endif // TPSADDCOURSETASK_H

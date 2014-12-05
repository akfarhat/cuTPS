#ifndef ADDCOURSETASK_H
#define ADDCOURSETASK_H

#include <QUuid>
#include <QDataStream>

#include "WorkerTask.h"
#include "Server.h"
#include "Entity/Course.h"

// TASK DATA FORMAT: |-- username --|-- password --|

class AddCourseTask : public WorkerTask
{
public:
    AddCourseTask(Server* srv);
    virtual void run();

};


#endif // ADDCOURSETASK_H

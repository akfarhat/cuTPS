#ifndef GETALLCOURSESSTASK_H
#define GETALLCOURSESSTASK_H

#include "WorkerTask.h"
#include "Server.h"

class GetAllCoursesTask : public WorkerTask
{
public:
    GetAllCoursesTask(Server* srv);
    virtual void run();
};

#endif // GETALLCOURSESSTASK_H

#ifndef GETALLBOOKSTASK_H
#define GETALLBOOKSTASK_H

#include "WorkerTask.h"
#include "Server.h"

class GetAllBooksTask : public WorkerTask
{
public:
    GetAllBooksTask(Server* srv);
    virtual void run();
};

#endif // GETALLBOOKSTASK_H

#ifndef BOOKLINKTASK_H
#define BOOKLINKTASK_H

#include "WorkerTask.h"
#include "Server.h"

class BookLinkTask : public WorkerTask
{
public:
    BookLinkTask(Server* srv);
    virtual void run();
};

#endif // BOOKLINKTASK_H

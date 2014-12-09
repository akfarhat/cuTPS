#ifndef ADDITEMTASK_H
#define ADDITEMTASK_H

#include <QUuid>
#include <QDataStream>

#include "WorkerTask.h"
#include "Server.h"

class AddItemTask : public WorkerTask
{
public:
    AddItemTask(Server* srv);
    virtual void run();
};

#endif // ADDITEMTASK_H

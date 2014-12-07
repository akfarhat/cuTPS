#ifndef RMITEMTASK_H
#define RMITEMTASK_H

#include <QUuid>
#include <QDataStream>

#include "WorkerTask.h"
#include "Server.h"

class RmItemTask : public WorkerTask
{
public:
    RmItemTask(Server* srv);
    virtual void run();
};

#endif // RMITEMTASK_H

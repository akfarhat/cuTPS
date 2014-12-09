#ifndef BANUSERTASK_H
#define BANUSERTASK_H

#include <QUuid>
#include <QDataStream>

#include "WorkerTask.h"
#include "Server.h"

class BanUserTask : public WorkerTask
{
public:
    BanUserTask(Server* srv);
    virtual void run();
};

#endif // BANUSERTASK_H

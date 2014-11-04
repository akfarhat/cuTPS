#ifndef TPSADDBOOKTASK_H
#define TPSADDBOOKTASK_H

#include <QUuid>
#include <QDataStream>

#include "TPSWorkerTask.h"
#include "Server.h"

class TPSAddBookTask : public TPSWorkerTask
{
public:
    TPSAddBookTask(Server* srv);
    virtual void run();

};

#endif // TPSADDBOOKTASK_H

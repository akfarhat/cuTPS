#ifndef TPSADDBOOKTASK_H
#define TPSADDBOOKTASK_H

#include <QUuid>
#include <QDataStream>

#include "TPSWorkerTask.h"
#include "Server.h"
#include "Entity/Textbook.h"

class TPSAddBookTask : public TPSWorkerTask
{
public:
    TPSAddBookTask(ServerAPI* srv);
    virtual void run();
};

#endif // TPSADDBOOKTASK_H

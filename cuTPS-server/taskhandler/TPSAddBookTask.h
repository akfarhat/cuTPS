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
    TPSAddBookTask(Server* srv);
    virtual void run();

protected:
    virtual void parseTextbook(Textbook*, QDataStream*);
};

#endif // TPSADDBOOKTASK_H

#ifndef ADDBOOKTASK_H
#define ADDBOOKTASK_H

#include <QUuid>
#include <QDataStream>

#include "WorkerTask.h"
#include "Server.h"
#include "Entity/Textbook.h"

class AddBookTask : public WorkerTask
{
public:
    AddBookTask(Server* srv);
    virtual void run();
};

#endif // ADDBOOKTASK_H

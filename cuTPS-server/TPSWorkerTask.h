#ifndef TPSWORKERTASK_H
#define TPSWORKERTASK_H

#include <QRunnable>
#include <QObject> // for singals+slots
#include <QUuid>
#include <QDebug>
#include <QTcpSocket>

#include "TPSClient.h"
#include "Server.h"

class TPSWorkerTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    TPSWorkerTask(Server *srv, QUuid sessionId);

signals:
    void result(int code);

protected:
    void run();

private:
    Server *server;
    QUuid sessionId;
};

#endif // TPSWORKERTASK_H

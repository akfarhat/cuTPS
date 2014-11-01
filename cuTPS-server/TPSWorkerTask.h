#ifndef TPSWORKERTASK_H
#define TPSWORKERTASK_H

#include <QRunnable>
#include <QObject> // for singals+slots
#include <QDebug>

class TPSWorkerTask : public QObject, public QRunnable
{
    Q_OBJECT
public:
    TPSWorkerTask();

signals:
    void result(int code);

protected:
    void run();
};

#endif // TPSWORKERTASK_H

#include "TPSClient.h"

TPSClient::TPSClient(QObject *parent) :
    QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(15); // BAD: TODO: shouldn't be called every time a new client is created + make dynamic thread count
}

void TPSClient::SetSocket(qintptr sockdescriptor)
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    socket->setSocketDescriptor(sockdescriptor);

    qDebug() << "New client on socket " << sockdescriptor;
}

void TPSClient::connected()
{
    qDebug() << "client connected event";
}

void TPSClient::disconnected()
{
    qDebug() << "client disconnected";
}

void TPSClient::readyRead()
{
    qDebug() << socket->readAll(); // just flush whatever is sent to us (TEMPORARY)

    // Create and run asynchronous task
    TPSWorkerTask *task = new TPSWorkerTask();
    task->setAutoDelete(true); // will be deleted automatically once finished

    connect(task, SIGNAL(result(int)), this, SLOT(taskResult(int)), Qt::QueuedConnection);

    QThreadPool::globalInstance()->start(task); // schedule to run in the pool
}

void TPSClient::taskResult(int code)
{
    QByteArray buffer;
    buffer.append("\r\nTask Result (code) = ");
    buffer.append(QString::number(code));

    socket->write(buffer); // send code to the client
}

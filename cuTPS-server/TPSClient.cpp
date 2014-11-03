#include "TPSClient.h"
#include "TPSServerAsync.h"
#include "Utils.h"
#include "Defines.h"

TPSClient::TPSClient(QObject *parent) :
    QObject(parent)
{
    if (!parent) return; // TODO: rework. Throw an exception if not an instance of TPSServerAsync

    server = ((TPSServerAsync*) parent)->getServer();
    blockSize = 0;
}

void TPSClient::setSocket(int sockdescriptor)
{
    socket = new QTcpSocket(this);

    connect(socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));

    socket->setSocketDescriptor(sockdescriptor);

    qDebug() << "New client on socket " << sockdescriptor;

    ServerResponse response = server->createSession();

    if (response.code == Fail)
    {
        // TODO: throw an exception
        qDebug() << "failed to create session!!";
        /* Temporary */ return;
    }

    sessionId = response.sessionID;

    qDebug() << "New Session. ID=" << sessionId;
}

void TPSClient::connected()
{
    qDebug() << "client connected event";
    // for some reason this func is never getting called
}

void TPSClient::disconnected()
{
    emit clientDisconnected(this);
}

void TPSClient::readyRead()
{
    QDataStream in(socket);
    in.setVersion(TPSConstants::PROTOCOL_VER);

    if (blockSize == 0)
    {
        if (socket->bytesAvailable() < sizeof(qint16))
        {
            return;
        }

        in >> blockSize;
    }

    if (socket->bytesAvailable() < blockSize)
    {
        return;
    }

    QString str;
    in >> str;
    qDebug() << "Got data: " << str;

    // Parse data

    // Create and run asynchronous task
    TPSWorkerTask *task = new TPSWorkerTask(server, sessionId);
    task->setAutoDelete(true); // will be deleted automatically once finished

    connect(task, SIGNAL(result(int)), this, SLOT(taskResult(int)), Qt::QueuedConnection);

    QThreadPool::globalInstance()->start(task); // schedule to run in the pool

    blockSize = 0;
}

void TPSClient::taskResult(int code)
{
    // send response
}

QUuid TPSClient::getSessionId() const
{
    return sessionId;
}

bool TPSClient::isConnected()
{
    return !(sessionId.isNull());
}

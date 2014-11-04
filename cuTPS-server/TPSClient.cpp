#include "TPSClient.h"
#include "TPSServerAsync.h"
#include "Utils.h"
#include "Defines.h"

#include <QByteArray>

#include "TPSAddBookTask.h"
#include "TPSLoginTask.h"

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

    TPSNetProtocol::NetRequest request;

    // Calculate data block size
    qint16 dataBlockSize = blockSize - sizeof(qint8) - sizeof(QUuid);
    // Allocate ByteArray of that size
    QByteArray* dataBlock = new QByteArray();
    dataBlock->resize(dataBlockSize);

    request.data = dataBlock;

    TPSNetUtils::DeserializeRequest(&request, &in);

    // Parse data

    TPSWorkerTask* task;

    QByteArray* responseBlock = new QByteArray(); // TODO: manage memory
    QDataStream out(responseBlock, QIODevice::WriteOnly);

    // Temporary router
    switch (request.invocation) {
    case TPSConstants::AddBook:
        task = new TPSAddBookTask(server);
        break;
    case TPSConstants::Login:
        task = new TPSLoginTask(server);
        break;
    }

    task->setInputDataBlock(dataBlock);
    task->setResponseDataBlock(responseBlock);
    task->setRequest(request);
    task->setSessionId(sessionId);

    task->setAutoDelete(true);
    connect(task, SIGNAL(result(int, QByteArray*)), this, SLOT(taskResult(int, QByteArray*)), Qt::QueuedConnection);
    QThreadPool::globalInstance()->start(task); // schedule to run in the pool

    blockSize = 0;
}

void TPSClient::taskResult(int code, QByteArray* response)
{
    qDebug() << "Task returned with code: " << code;
    socket->write(*response);
}

QUuid TPSClient::getSessionId() const
{
    return sessionId;
}

bool TPSClient::isConnected()
{
    return !(sessionId.isNull());
}

#include "NetClient.h"
#include "ServerAsync.h"
#include "Utils.h"
#include "TPSNetUtils.h"
#include "Defines.h"
#include "TPSNetUtils.h"

#include <QByteArray>

#include "ClientTaskHandling/AddBookTask.h"
#include "ClientTaskHandling/LoginTask.h"
#include "ClientTaskHandling/AddCourseTask.h"
#include "ClientTaskHandling/GetBookDetailsTask.h"
#include "ClientTaskHandling/GetRequiredBooksTask.h"
#include "ClientTaskHandling/SubmitOrderTask.h"

NetClient::NetClient(QObject *parent) :
    QObject(parent)
{
    if (!parent) return; // TODO: rework. Throw an exception if not an instance of TPSServerAsync

    server = ((ServerAsync*) parent)->getServer();
    blockSize = 0;
}

void NetClient::setSocket(int sockdescriptor)
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

void NetClient::connected()
{
    qDebug() << "client connected event";
    // for some reason this func is never getting called
}

void NetClient::disconnected()
{
    server->closeSession(sessionId);
    emit clientDisconnected(this);
}

void NetClient::readyRead()
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

    WorkerTask* task;

    QByteArray* responseBlock = new QByteArray(); // TODO: manage memory
    QDataStream out(responseBlock, QIODevice::WriteOnly);

    // Temporary router
    switch (request.invocation) {

    case TPSConstants::AddBook:
        task = new AddBookTask(server);
        break;
    case TPSConstants::AddCourse:
        task = new AddCourseTask(server);
        break;
    case TPSConstants::GetBookDetails:
        task = new GetBookDetailsTask(server);
        break;
    case TPSConstants::GetRequiredBooks:
        task = new GetRequiredBooksTask(server);
        break;
    case TPSConstants::Login:
        task = new LoginTask(server);
        break;
    case TPSConstants::SubmitOrder:
        task = new SubmitOrderTask(server);
        break;
    case TPSConstants::Goodbye:
    default:
        // kill the client
        server->closeSession(sessionId);
        emit clientDisconnected(this);
        return;
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

void NetClient::taskResult(int code, QByteArray* response)
{
    qDebug() << "Task returned with code: " << code;
    socket->write(*response);
}

QUuid NetClient::getSessionId() const
{
    return sessionId;
}

bool NetClient::isConnected()
{
    return !(sessionId.isNull());
}

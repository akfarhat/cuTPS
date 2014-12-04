#include "NetClient.h"
#include "ServerAsync.h"
#include "Utils.h"
#include "Defines.h"

#include <QByteArray>

#include "ClientTaskHandling/AddBookTask.h"
#include "ClientTaskHandling/LoginTask.h"
#include "ClientTaskHandling/AddCourseTask.h"
#include "ClientTaskHandling/GetBookDetailsTask.h"
#include "ClientTaskHandling/GetRequiredBooksTask.h"
#include "ClientTaskHandling/SubmitOrderTask.h"

using namespace TPSNetProtocolDefs;

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
    in.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

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

    // the worker task will delete it
    NetRequest* request = new NetRequest();

    try {
        in >> *request;
    } catch (NetMessage::BadRequestException* e) {
        qDebug() << e->what();
        socket->abort();
        return;
    }

    // Parse data
    WorkerTask* task;

    // Temporary router
    switch (request->getInvocation()) {

    case AddBook:
        task = new AddBookTask(server);
        break;
    case AddCourse:
        task = new AddCourseTask(server);
        break;
    case GetBookDetails:
        task = new GetBookDetailsTask(server);
        break;
    case GetRequiredBooks:
        task = new GetRequiredBooksTask(server);
        break;
    case Login:
        task = new LoginTask(server);
        break;
    case SubmitOrder:
        task = new SubmitOrderTask(server);
        break;
    case Goodbye:
    default:
        // kill the client
        socket->abort();
        return;
    }

    task->setRequest(request);
    task->setSessionId(sessionId);
    task->setAutoDelete(true);

    connect(task,
            SIGNAL(result(int, NetResponse*)),
            this,
            SLOT(taskResult(int, NetResponse*)),
            Qt::QueuedConnection);

    QThreadPool::globalInstance()->start(task); // schedule to run in the pool

    blockSize = 0;
}

void NetClient::taskResult(int code, NetResponse* response)
{
    qDebug() << "Task returned with code: " << code;
    qDebug() << "Task also returned response: " << response->stringRepr();
    QByteArray responseBytes;
    QDataStream out(&responseBytes, QIODevice::WriteOnly);
    out << *response;
    qint64 written = socket->write(responseBytes);
    qDebug() << "Send to client (bytes): " << written;
    delete response;
}

QUuid NetClient::getSessionId() const
{
    return sessionId;
}

bool NetClient::isConnected()
{
    return !(sessionId.isNull());
}

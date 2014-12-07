#include "NetClient.h"

#include <functional>

#include <QByteArray>
#include <QMap>

#include "ServerAsync.h"
#include "Defines.h"

#include "ClientTaskHandling/LoginTaskFactory.h"
#include "ClientTaskHandling/UserTaskFactory.h"
#include "ClientTaskHandling/ContentMgrTaskFactory.h"
#include "ClientTaskHandling/AdminTaskFactory.h"
#include "ClientTaskHandling/SUTaskFactory.h"

using namespace TPSNetProtocolDef;

NetClient::NetClient(QObject *parent) :
    QObject(parent)
{
    if (!parent) return; // TODO: rework. Throw an exception if not an instance of TPSServerAsync

    server = ((ServerAsync*) parent)->getServer();
    blockSize = 0;
    taskFactory = nullptr;
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
    clientStatusUpdated();

    qDebug() << "New Session. ID=" << sessionId;
}

void NetClient::kick()
{
    if (isConnected()) socket->abort();
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
    in.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

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
    } catch (NetMessage::BadRequestException& e) {
        qDebug() << e.what();
        kick();
        return;
    }

    // Check if this is goodbye msg first
    if (request->getInvocation() == IGoodbye)
        kick();

    WorkerTask* task;

    try {
        task = taskFactory->createTask(server, request->getInvocation());
    } catch (TaskAbsFactory::PermissionDeniedExc& e) {
        qDebug() << e.what();
        kick();
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
    if (response->getInvocation() == ILogin &&
            response->getResponseCode() == 0x1)
    {
        clientStatusUpdated();
    }

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

void NetClient::clientStatusUpdated()
{
    // Client has successfully went through login process.
    // Now must get an appororiate task factory for new priv.

    auto anonymousFactoryCreator = []()
    {
        return new LoginTaskFactory();
    };

    auto studentFactoryCreator = []()
    {
        return new UserTaskFactory();
    };

    auto cmFactoryCreator = []()
    {
        return new ContentMgrTaskFactory();
    };

    auto adminFactoryCreator = []()
    {
        return new AdminTaskFactory();
    };

    auto superuserFactoryCreator = []()
    {
        return new SUTaskFactory();
    };

    QMap<UsrPermissionGroup, std::function<TaskAbsFactory*(void)>> map;
    map.insert(UsrAnonymous, anonymousFactoryCreator);
    map.insert(UsrStu, studentFactoryCreator);
    map.insert(UsrCm, cmFactoryCreator);
    map.insert(UsrAdm, adminFactoryCreator);
    map.insert(UsrSuperuser, superuserFactoryCreator);

    // TODO: request user permission group from the server passing sessionID
    UsrPermissionGroup grp = UsrSuperuser;

    if (this->taskFactory) delete this->taskFactory;
    this->taskFactory = map[grp]();
}

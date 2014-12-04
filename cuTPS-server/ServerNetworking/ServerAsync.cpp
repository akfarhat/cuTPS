#include "ServerAsync.h"

#include <iostream>
#include "Defines.h"
#include "ServerPrefs.h"

ServerAsync::ServerAsync(QObject *parent) :
    QTcpServer(parent)
{

}

void ServerAsync::StartServer()
{
    const int port = ServerPrefs::GetPort();
    const int thrCap = ServerPrefs::MaxThreads();
    QThreadPool::globalInstance()->setMaxThreadCount(thrCap);

    if (listen(QHostAddress::Any, port))
    {
        qDebug() << " >> Server Started on port " << port;
        qDebug() << "\tMax parallel threads: " << thrCap;
        // TODO: ensure that parent destroys its children
        server = new Server(this);
        emit serverStarted();
    }
    else
    {
        qDebug() << " >> Server has failed to listen on port " << port
                  << " Error: " << serverError();

        emit serverFailure();
    }
}

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
void ServerAsync::incomingConnection(int handle)
#else
void ServerAsync::incomingConnection(qintptr handle)
#endif
{                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
    NetClient *client = new NetClient(this);
    connect(client, SIGNAL(clientDisconnected(NetClient*)), this, SLOT(clientDisconnected(NetClient*)));
    client->setSocket(handle);
}

void ServerAsync::clientDisconnected(NetClient *client)
{
    QUuid sessionId = client->getSessionId();
    qDebug() << "client disconnected: " << sessionId;
    // TODO: Invalidate sessionId
    // delete client;
}

Server* ServerAsync::getServer() const
{
    return server;
}


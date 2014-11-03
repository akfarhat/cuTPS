#include "TPSServerAsync.h"

#include <iostream>
#include "Defines.h"

TPSServerAsync::TPSServerAsync(QObject *parent) :
    QTcpServer(parent)
{

}

void TPSServerAsync::StartServer()
{
    if (listen(QHostAddress::Any, TPSConstants::PORT))
    {
        std::cout << " >> Server Started on port " << TPSConstants::PORT << std::endl;
        // TODO: ensure that parent destroys its children
        server = new Server(this);
        emit serverStarted();
    }
    else
    {
        std::cerr << " >> Server has failed to listen on port " << TPSConstants::PORT << std::endl;
        emit serverFailure();
    }
}

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
void TPSServerAsync::incomingConnection(int handle)
#else
void TPSServerAsync::incomingConnection(qintptr handle)
#endif
{
    TPSClient *client = new TPSClient(this);
    connect(client, SIGNAL(clientDisconnected(TPSClient*)), this, SLOT(clientDisconnected(TPSClient*)));
    client->setSocket(handle);
}

void TPSServerAsync::clientDisconnected(TPSClient *client)
{
    QUuid sessionId = client->getSessionId();
    qDebug() << "client disconnected: " << sessionId;
    // TODO: Invalidate sessionId
    delete client;
}

Server* TPSServerAsync::getServer() const
{
    return server;
}


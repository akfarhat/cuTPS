#include "TPSServerAsync.h"

TPSServerAsync::TPSServerAsync(QObject *parent) :
    QTcpServer(parent)
{
}

void TPSServerAsync::StartServer()
{
    if (listen(QHostAddress::Any, PORT))
    {
        qDebug() << " >> Server Started";
    }
    else
    {
        qDebug() << " >> ! Server didn't start";
    }
}

void TPSServerAsync::incomingConnection(int handle)
{
    TPSClient *client = new TPSClient(this);
    client->SetSocket(handle);
}

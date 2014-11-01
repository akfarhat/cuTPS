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

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
void TPSServerAsync::incomingConnection(int handle)
#else
void TPSServerAsync::incomingConnection(qintptr handle)
#endif
{
    TPSClient *client = new TPSClient(this);
    client->SetSocket(handle);
}

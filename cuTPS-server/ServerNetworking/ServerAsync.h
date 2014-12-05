// Class: TPCServerAsync
// Type: Control
// Description:
//     This is the main execution thread for the cuTPS server.
//     once started, this object listens on an available socket
//     and handles each request by creating a TPSClient for communication

#ifndef SERVERASYNC_H
#define SERVERASYNC_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

#include "NetClient.h"
#include "Server.h"

class ServerAsync : public QTcpServer
{
    Q_OBJECT
public:
    explicit ServerAsync(QObject *parent = 0);
    void StartServer();

    Server *getServer() const;

protected:

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    void incomingConnection(int handle);
#else
    void incomingConnection(qintptr handle);
#endif

signals:
    void serverStarted();
    void serverFailure();

public slots:
    void clientDisconnected(NetClient*);

private:
    Server *server;

};

#endif // SERVERASYNC_H

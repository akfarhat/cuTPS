// Class: TPCServerAsync
// Type: Control
// Description:
//     This is the main execution thread for the cuTPS server.
//     once started, this object listens on an available socket
//     and handles each request by creating a TPSClient for communication

#ifndef TPSSERVERASYNC_H
#define TPSSERVERASYNC_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include <QDebug>

#include "TPSClient.h"
#include "Server.h"

class TPSServerAsync : public QTcpServer
{
    Q_OBJECT
public:
    explicit TPSServerAsync(QObject *parent = 0);
    void StartServer();

    ServerAPI *getServer() const;

protected:

#if QT_VERSION < QT_VERSION_CHECK(5,0,0)
    void incomingConnection(int handle);
#else
    void incomingConnection(qintptr handle);
#endif

signals:
    void serverStarted();
    void serverFailure(); // not implemented

public slots:
    void clientDisconnected(TPSClient*);

private:
    ServerAPI *server;

};

#endif // TPSSERVERASYNC_H

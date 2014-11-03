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

    Server *getServer() const;

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
    Server *server;

};

#endif // TPSSERVERASYNC_H

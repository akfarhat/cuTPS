#ifndef TPSCLIENT_H
#define TPSCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>
#include <QUuid>

#include "TPSWorkerTask.h"
#include "Server.h"
#include "Entity/User.h"

class TPSClient : public QObject
{
    Q_OBJECT
public:
    explicit TPSClient(QObject *parent = 0);
    void setSocket(int sockdescriptor);
    bool isConnected();

    QUuid getSessionId() const;

signals:
    void clientDisconnected(TPSClient*);

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void taskResult(int code);

private:
    Server *server;
    QTcpSocket *socket;
    QUuid sessionId;
    User *user;
    qint16 blockSize;
};

#endif // TPSCLIENT_H

// Class: TPSClient
// Type: Control
// Description:
//     This class is responsible for handling the communication
//     over TCP sockets between the server and the client for
//     each request instance. Once the connection handle is established
//     from the TPSServerAsync control flow, it will takeover the request,
//     creating the appropriate entity objects from the data sent
//     over the network.
//     It offloads the actual request to a separate thread

#ifndef TPSCLIENT_H
#define TPSCLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QByteArray>
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
    // Event emitted when the client connection is closed
    void clientDisconnected(TPSClient*);

public slots:
    // Event handlers for events emitted by the TCP socket object
    void connected();
    void disconnected();
    // Event handler called when data has been received by the client
    void readyRead();
    // Event handler for the completion of the asynchronouse task
    void taskResult(int code, QByteArray* response);

private:
    // Reference to the server API that will handle updating
    // the system state or gathering data for a this request instance
    Server *server;
    // The socket object wrapper provided by the QT framework
    QTcpSocket *socket;
    // The session ID belonging to this request
    QUuid sessionId;
    // A reference to the client user
    User *user;
    // The size of of data from each read of the socket buffer
    qint16 blockSize;
};

#endif // TPSCLIENT_H

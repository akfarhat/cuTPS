#ifndef CLIENTNETWORKHANDLER_H
#define CLIENTNETWORKHANDLER_H

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>
#include <QUuid>
#include <QVector>
#include <QDataStream>

#include "Utils.h"
#include "Entity/Textbook.h"
// Class: ClientNetworkHandler
// Type: Control
// Description:
//     This class offers the client side API for possible
//     requests to the server.

#include "Entity/Order.h"
#include "Entity/Course.h"

// Note, this could inherit from a NetworkHandler
// that manages the networking
class ClientNetworkHandler : public QObject {
    Q_OBJECT

public:
    ClientNetworkHandler();
    virtual ~ClientNetworkHandler();
    // These methods should serialize the data and
    // send it to the Server

    // Establish a TCP connection to the address and port
    void connectToServer(QHostAddress&, int port);

    // Disconnect from the server
    void disconnectFromServer();

    // Login to the server - request a session id
    QUuid login(UserCredentials&);

    // Request the list of available textbooks
    // for the user with this session.
    QUuid getRequiredBooks();

    // Request the details of a particular textbook
    QUuid getBookDetails(Textbook&);

    // Submit an order to the server
    QUuid submitOrder(Order&);

    // Add a course to the content availability of the system
    QUuid addCourse(Course&);

    // Add a textbook to the content availability of the system
    QUuid addBook(Textbook&);

    // Access modifiers for the state of the connection to the server
    QTcpSocket::SocketState getSocketState() const;
    bool isConnected() const;
    bool isValid() const; // i.e. connected && logged in

signals:
    // Events emitted regarding the network status
    void connectedToServer();
    void disconnectedFromServer();
    void networkError(QAbstractSocket::SocketError);
    void serverError(QUuid requestId, int code);

    // Events emitted regarding the completion of server API
    void loginSuccessful(QUuid requestId);
    void orderStatusReceived(QUuid requestId, int code);
    void updateCompleted(QUuid requestId, int code);
    void textbookDetailsReceived(QUuid requestId, int code, Textbook*);
    void textbookLookupCompleted(QUuid requestId, int code, QVector<Textbook*>*);

public slots:
    // Event handlers for events emitted by the TCP socket object
    void connected();
    void disconnected();
    void readyRead();
    void aboutToClose();
    void error(QAbstractSocket::SocketError);

private:
    // Connection to the server
    QTcpSocket *connection;
    SessionCredentials session;
    bool loggedIn;
    // Block size for reads from the connection
    qint16 blockSize;

};

#endif // CLIENTNETWORKHANDLER_H

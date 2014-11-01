#ifndef CLIENTNETWORKHANDLER_H
#define CLIENTNETWORKHANDLER_H

#include <QObject>
#include <QHostAddress>
#include <QTcpSocket>
#include <QUuid>
#include <QVector>

#include "Utils.h"
#include "Entity/Textbook.h"
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
    // send it to the ServerNetworkHandler

    void connectToServer(QHostAddress&, int port);
    void disconnectFromServer();

    QUuid login(UserCredentials&);
    QUuid getRequiredBooks();
    QUuid getBookDetails(Textbook&);
    QUuid submitOrder(Order&);
    QUuid addCourse(Course&);
    QUuid addBook(Textbook&);

    QTcpSocket::SocketState getSocketState() const;
    bool isConnected() const;
    bool isValid() const; // i.e. connected && logged in

signals:
    void connectedToServer();
    void disconnectedFromServer();

    void networkError(QAbstractSocket::SocketError);
    void serverError(QUuid requestId, int code);

    void loginSuccessful(QUuid requestId);
    void orderStatusReceived(QUuid requestId, ServerResponse*);
    void updateCompleted(QUuid requestId, ServerResponse*);

    void textbookDetailsReceived(QUuid requestId, ServerResponse*, Textbook*);
    void textbookLookupCompleted(QUuid requestId, ServerResponse*, QVector<Textbook*>*);

public slots:
    void connected();
    void disconnected();
    void readyRead();
    void aboutToClose();
    void error(QAbstractSocket::SocketError);

private:
    QTcpSocket *connection;
    SessionCredentials session;
    bool loggedIn;
};

#endif // CLIENTNETWORKHANDLER_H

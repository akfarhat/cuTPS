#ifndef CLIENTNETWORKHANDLER_H
#define CLIENTNETWORKHANDLER_H

// Class: ClientNetworkHandler
// Type: Control
// Description:
//     This class offers the client side API for possible
//     requests to the server.

// === API change history === //
// Dec, 2:      --- getBookDetails() now take just the IDs of textbooks
//                  getBookDetail(qint32) <- will return a single textbook with that id
//                  getBookDetail(QVector<qint32>&) <- will return a vector of books.
//
//              --- textbookDetailsReceived(QUuid requestId, int code, QVector<Textbook*>* books)
//                  now returns vector of textbook pointers. All textbooks and vector itself are
//                  created using new, so delete them after use. qDeleteAll().
//                  You may want to use qDeleteAll(const Container& c) from <QtAlgorithms> header.
//
//              --- void textbookLookupCompleted(QUuid requestId, int code, QVector<qint32>* booksIds)
//                  also returns a vector of book ids. You can pass the output right to getBookDetails() 
//                  to receive details about all of them in one bunch, via textbookDetailsReceived().
//
//              --- getRequiredBooks() now returns only IDs of books for performance reasons.
//                  Use chained requests to receive ids first, then details.
//
//                  <woyorus>

#include <QObject>
#include <QMetaObject>
#include <QHostAddress>
#include <QTcpSocket>
#include <QUuid>
#include <QVector>
#include <QDataStream>

#include "Defines.h"
#include "Utils.h"
#include "Entity/Textbook.h"
#include "Entity/Order.h"
#include "Entity/Course.h"

using namespace TPSNetProtocolDefs;

// metatype declarations for correct signalling
Q_DECLARE_METATYPE(QVector<Textbook*>*)
Q_DECLARE_METATYPE(QVector<qint32>*)

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
    // TODO: it makes sense to return course objects with linked textbooks
    QUuid getRequiredBooks(QString&);

    // Request the details of a particular textbook id
    QUuid getBookDetails(const qint32 id);

    // Request details for a list of textbook ids
    QUuid getBookDetails(const QVector<qint32>& ids);

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
    // Events emitted regarding the network events
    void connectedToServer();
    void disconnectedFromServer();
    void networkError(QAbstractSocket::SocketError);
    void serverError(QUuid requestId, int code);

    // Events emitted regarding the completion of server API call
    void loginSuccessful(QUuid requestId, Role userRole);
    void loginFailed(QUuid requestId);
    void orderStatusReceived(QUuid requestId, int code);
    void updateCompleted(TPSNetProtocolDefs::InvocationDescriptor, QUuid requestId, int code);
    // Books in vector are created using new. Delete them using delete after use.
    void textbookDetailsReceived(QUuid requestId, int code, QVector<Textbook*>* books);
    void textbookLookupCompleted(QUuid requestId, int code, QVector<qint32>* booksIds);

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

#ifndef CLIENTNETWORKHANDLER_H
#define CLIENTNETWORKHANDLER_H

// Class: ClientNetworkHandler
// Type: Control
// Description:
//     This class offers the client side API for possible
//     requests to the server.

// === API change history === //
// Dec, 2:      --- getBookDetails() now takes just the IDs of textbooks
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
//                  to receive details about all of them in one bunch, via textbookDetailsReceived().'''''''''''''''''''
//
//                  <woyorus>

#include <QObject>
#include <QMetaObject>
#include <QHostAddress>
#include <QTcpSocket>
#include <QUuid>
#include <QVector>
#include <QMap>
#include <QDataStream>

#include "Defines.h"

#include "Entity/Textbook.h"
#include "Entity/Chapter.h"
#include "Entity/Section.h"
#include "Entity/Order.h"
#include "Entity/Course.h"
#include "Entity/User.h"

using namespace TPSNetProtocolDef;
using namespace TPSDef;

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

    // What: Request the list of _available_ (available==true) textbooks
    // for the user on this session. Note: textbooks include sections and chapters
    // Related reply signal: textbookDetailsReceived(QUuid,int,QMap<Course, QSet<Textbook>>*)
    // -- use QSet<Textbook>* uniqueBooks(QMap<Course, QSet<Textbook>*); to get books only
    QUuid getRequiredBooks();

    // What: Request for all the books registered (including unavailable ones)
    // Note: textbooks include sections and chapters
    // Related reply signal: textbookDetailsReceived(QUuid,int,QMap<Course, QSet<Textbook>>*)
    // -- use QSet<Textbook>* uniqueBooks(QMap<Course, QSet<Textbook>*); to get books only
    QUuid getAllBooks();
    QUuid getAllCourses();

    // What: Request the details (i.e. Textbook object itself) of a particular textbook id
    // Note: textbooks include sections and chapters
    // Related reply signal: textbookDetailsReceived(QUuid,int,QMap<Course, QSet<Textbook>>*)
    // -- use QSet<Textbook>* uniqueBooks(QMap<Course, QSet<Textbook>*); to get the book only
    QUuid getBookDetails(const qint32 id);

    // What: Request details for a list of textbook ids
    // Note: textbooks include sections and chapters
    // Related reply signal: textbookDetailsReceived(QUuid,int,QMap<Course, QSet<Textbook>>*)
    // -- use QSet<Textbook>* uniqueBooks(QMap<Course, QSet<Textbook>*); to get the books only
    QUuid getBookDetails(const QVector<int>& ids);

    // What: Submit an order to the server
    // Reltated reply signal: orderStatusReceived(QUuid, int);
    QUuid submitOrder(Order&);

    // What: Add a new course to the system.
    // Related reply signal: updateCompleted(QUuid, int, InvocationDescriptor, qint32)
    QUuid addCourse(Course&);
    QUuid linkTextbook(qint32 courseId, qint32 textId);
    QUuid unlinkTextbook(qint32 courseId, qint32 textId);

    // Add a textbook to the content availability of the system
    // Related reply signal: updateCompleted(QUuid, int, InvocationDescriptor, qint32)
    QUuid addBook(Textbook&);
    QUuid addChapter(qint32 textId, Chapter&);
    QUuid addSection(qint32 textId, qint32 chId, Section&);

    QUuid removeBook(qint32 id);
    QUuid removeChapter(qint32 id);
    QUuid removeSection(qint32 id);

    QUuid addUser(User&);
    QUuid banUser(qint32 uid);

    // Access modifiers for the state of the connection to the server
    QTcpSocket::SocketState getSocketState() const;
    bool isConnected() const;
    bool isValid() const; // i.e. connected && logged in

    // TODO: implement
    static QSet<Textbook*>* uniqueBooks(QMap<Course*, QSet<Textbook*>*>*);

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
    void updateCompleted(QUuid requestId, int code, InvocationDescriptor invo, qint32 id);

    // Books in vector are created using new. Delete them using delete after use.
    void textbookDetailsReceived(QUuid requestId, int code, QVector<Textbook*>* books);
    void textbookLookupCompleted(QUuid requestId, int code, QMap<Course*, QSet<Textbook*>*>*);
    void courseLookupCompleted(QUuid requestId, int code, QVector<Course*>* courses);

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

#ifndef CLIENTNETWORKHANDLER_H
#define CLIENTNETWORKHANDLER_H

// Class: ClientNetworkHandler
// Type: Control
// Description:
//     This class offers the client side API for possible
//     requests to the server.

#include <QObject>
#include <QMetaObject>
#include <QHostAddress>
#include <QTcpSocket>
#include <QUuid>
#include <QVector>
#include <QList>
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
typedef QMap<Course*, QList<Textbook*>*>* CourseTextMap;
Q_DECLARE_METATYPE(CourseTextMap)
Q_DECLARE_METATYPE(Textbook*)
Q_DECLARE_METATYPE(QList<Textbook*>*)
Q_DECLARE_METATYPE(QList<Course*>*)

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

    // What: attemt to log in into the server.
    // Available for: anonymous user.
    // Related reply: loginSuccessful / loginFailed.
    QUuid login(UserCredentials&);

    //// STUDENT USER OPERATIONS

    // What: Request the list of _available_ (available==true) textbooks
    // for the user on this session. Note: textbooks include sections and chapters
    // Related reply signal: requiredBooksReceived()
    QUuid getRequiredBooks();

    // What: Submit an order to the server
    // Reltated reply signal: orderStatusReceived(QUuid, int);
    QUuid submitOrder(Order&);

    //// STUDENT + CONTENT MANAGER OPERATIONS

    // What: Request the details (i.e. Textbook object itself) of a particular textbook id
    // Note: textbooks include sections and chapters
    // Available for: Students, ContentManagers.
    // Related reply signal: textbookRecevied(Textbook*)
    QUuid getBookDetails(const qint32 id);

    // What: Request details for a list of textbook ids
    // Note: textbooks include sections and chapters
    // Available for: Students, ContentManagers.
    // Related reply signal: textbookListReceived(QList<Textbook*>*)
    QUuid getBookDetails(const QVector<qint32>& ids);

    //// CONTENT MANAGER OPERATIONS

    // What: Request for all the books registered (including unavailable ones)
    // Note: textbooks include sections and chapters
    // Available for: ContentManagers
    // Related reply signal: textbookListReceived(QList<Textbook*>*)
    QUuid getAllBooks();

    // What: request a list of all courses in the system.
    // Available for: content managers
    // Related reply signal: courseListRecevied(QList<Course*>*)
    QUuid getAllCourses();

    // What: Add a new course to the system.
    // Available for content managers
    // Related reply signal: updateCompleted(QUuid, int, InvocationDescriptor, qint32)
    QUuid addCourse(Course&);

    // What: assign an existing textbook to an existing course
    // Available for content managers
    // Related reply signal: updateCompleted() --- returns courseId in id arg.
    QUuid linkTextbook(qint32 courseId, qint32 textId);

    // What: remove a linked textbook from course.
    // Available for content managers
    // Related reply signal: updateCompleted() --- returns courseId in id arg.
    QUuid unlinkTextbook(qint32 courseId, qint32 textId);

    // Add new items routines.
    // Available for content managers.
    // Related reply signal: updateCompleted(QUuid, int, InvocationDescriptor, qint32)
    QUuid addBook(Textbook&);
    QUuid addChapter(qint32 textId, Chapter&);
    QUuid addSection(qint32 textId, qint32 chId, Section&);


    // What: removing items routines
    // Available for content managers.
    // Related reply signal: updateCompleted(QUuid, int, InvocationDescriptor, qint32)
    QUuid removeBook(qint32 id);
    QUuid removeChapter(qint32 id);
    QUuid removeSection(qint32 id);

    // CONTENT MANAGERS + ADMINISTRATOR OPERATIONS

    // What: add a new user to the system.
    // Available for: ContentManagers, Administrators.
    // Note: ContentManagers cannot add administrator users.
    // Reletaed reply: updateCompete()
    QUuid addUser(User&);

    // ADMINISTRATOR OPERATIONS

    // What: flags user as inactive. 
    // Available for: administrators
    // Related reply: updateCompleted()
    QUuid banUser(qint32 uid);

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
    void updateCompleted(QUuid requestId, int code, InvocationDescriptor invo, qint32 id);

    // Books in vector are created using new. Delete them using delete after use.
    void requiredBooksReceived(QUuid requestId, int code, QMap<Course*, QList<Textbook*>*>*);
    void textbookReceived(QUuid requestId, int code, Textbook* text);
    void textbookListReceived(QUuid requestId, int code, QList<Textbook*>*);
    void courseListReceived(QUuid requestId, int code, QList<Course*>*);

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

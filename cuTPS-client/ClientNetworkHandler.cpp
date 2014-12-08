#include "ClientNetworkHandler.h"

#include <QString>
#include <QVector>
#include <QDebug>
#include <iostream>

#include "Entity/NetRequest.h"
#include "Entity/NetResponse.h"

#include "Defines.h"

#define ASSERT_VALID                                                    \
    if (!isValid())                                                     \
    {                                                                   \
        qDebug() << "error: invocation attempt on invalid socket";      \
        return QUuid();                                                 \
    }                                                                   \

using namespace TPSNetProtocolDef;

ClientNetworkHandler::ClientNetworkHandler()
{
    connection = new QTcpSocket(this);

    connect(connection, SIGNAL(connected()), this, SLOT(connected()));
    connect(connection, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(connection, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(connection, SIGNAL(aboutToClose()), this, SLOT(aboutToClose()));
    connect(connection, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(error(QAbstractSocket::SocketError)));

    loggedIn = false;
    blockSize = 0;
}

ClientNetworkHandler::~ClientNetworkHandler()
{
    if (getSocketState() != QTcpSocket::UnconnectedState)
    {
        connection->close();
    }

    // delete connection; // this handler is a parent, so we don't have to worry about deletion.
}

void ClientNetworkHandler::connectToServer(QHostAddress& addr, int port)
{
    session.sessionID = -1;
    session.username = "";
    connection->abort();
    connection->connectToHost(addr, port, QIODevice::ReadWrite);
}

void ClientNetworkHandler::disconnectFromServer()
{
    if (isConnected())
    {
        connection->disconnectFromHost();
        connection->close();
    }

    loggedIn = false;
    session.sessionID = -1;
    session.username = "";
}

QUuid ClientNetworkHandler::login(UserCredentials& credentials)
{
    if (!isConnected())
    {
        qDebug() << "error: invocation attempt on invalid socket";
        return QUuid();
    }

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(ILogin);
    request.setRequestId(requestId);

    QByteArray data;
    QDataStream outDataStream(&data, QIODevice::WriteOnly);

    outDataStream << credentials.username << credentials.password;

    request.setData(data);

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    outStream << request;

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::getRequiredBooks()
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(IGetRequiredBooks);
    request.setRequestId(requestId);

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    outStream << request;

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::getAllCourses()
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(IGetAllCourses);
    request.setRequestId(requestId);

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    outStream << request;

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::getBookDetails(const qint32 id)
{
    return getBookDetails(QVector<qint32>({id}));
}

QUuid ClientNetworkHandler::getBookDetails(const QVector<qint32>& ids)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(IGetBookDetails);
    request.setRequestId(requestId);

    QByteArray data;
    QDataStream outDataStream(&data, QIODevice::WriteOnly);

    qDebug() << "forming book request for these guys: " << ids;

    outDataStream << ids;

    request.setData(data);

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    outStream << request;

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::linkTextbook(qint32 courseId, qint32 textId)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(IBookLink);
    request.setRequestId(requestId);

    QByteArray data;
    QDataStream outDataStream(&data, QIODevice::WriteOnly);

    outDataStream << courseId << textId;

    request.setData(data);

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    outStream << request;

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::unlinkTextbook(qint32 courseId, qint32 textId)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(IBookUnlink);
    request.setRequestId(requestId);

    QByteArray data;
    QDataStream outDataStream(&data, QIODevice::WriteOnly);

    outDataStream << courseId << textId;

    request.setData(data);

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    outStream << request;

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::submitOrder(Order& order)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(ISubmitOrder);
    request.setRequestId(requestId);

    QByteArray data;
    QDataStream outDataStream(&data, QIODevice::WriteOnly);

    outDataStream << order;

    request.setData(data);

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    outStream << request;

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::addCourse(Course& course)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(IAddCourse);
    request.setRequestId(requestId);

    QByteArray data;
    QDataStream outDataStream(&data, QIODevice::WriteOnly);

    outDataStream << course;

    request.setData(data);

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    outStream << request;

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::addBook(Textbook& text)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(IAddBook);
    request.setRequestId(requestId);

    QByteArray data;
    QDataStream outDataStream(&data, QIODevice::WriteOnly);

    outDataStream << text;

    request.setData(data);

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    outStream << request;

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::addChapter(qint32 textId, Chapter& c)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(IAddChapter);
    request.setRequestId(requestId);

    QByteArray data;
    QDataStream outDataStream(&data, QIODevice::WriteOnly);

    outDataStream << textId;
    outDataStream << c;

    request.setData(data);

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    outStream << request;

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::addSection(qint32 textId, qint32 chId, Section& s)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(IAddSection);
    request.setRequestId(requestId);

    QByteArray data;
    QDataStream outDataStream(&data, QIODevice::WriteOnly);

    outDataStream << textId << chId << s;

    request.setData(data);

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    outStream << request;

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::removeBook(qint32 id)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(IRmBook);
    request.setRequestId(requestId);

    QByteArray data;
    QDataStream outDataStream(&data, QIODevice::WriteOnly);

    outDataStream << id;

    request.setData(data);

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    outStream << request;

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::removeChapter(qint32 id)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(IRmChapter);
    request.setRequestId(requestId);

    QByteArray data;
    QDataStream outDataStream(&data, QIODevice::WriteOnly);

    outDataStream << id;

    request.setData(data);

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    outStream << request;

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::removeSection(qint32 id)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(IRmSection);
    request.setRequestId(requestId);

    QByteArray data;
    QDataStream outDataStream(&data, QIODevice::WriteOnly);

    outDataStream << id;

    request.setData(data);

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    outStream << request;

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::addStudentUser(Student& usr, QString passwd)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(IAddUser);
    request.setRequestId(requestId);

    QByteArray data;
    QDataStream outDataStream(&data, QIODevice::WriteOnly);

    outDataStream << usr;

    request.setData(data);

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    outStream << request;

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::banUser(qint32 uid)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(IBanUser);
    request.setRequestId(requestId);

    QByteArray data;
    QDataStream outDataStream(&data, QIODevice::WriteOnly);

    outDataStream << uid;

    request.setData(data);

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    outStream << request;

    connection->write(requestBytes);

    return requestId;
}

QTcpSocket::SocketState ClientNetworkHandler::getSocketState() const
{
    return connection->state();
}

bool ClientNetworkHandler::isConnected() const
{
    qDebug() << "SocketState: " << getSocketState();
    return getSocketState() == QTcpSocket::ConnectedState ||
           getSocketState() == QTcpSocket::BoundState;
}

bool ClientNetworkHandler::isValid() const
{
    return isConnected() && loggedIn;
}

/* public slots */

void ClientNetworkHandler::connected()
{
    qDebug() << "connected to server";
    emit connectedToServer();
}

void ClientNetworkHandler::disconnected()
{
    qDebug() << "disconnected from server";
    emit disconnectedFromServer();
}

void ClientNetworkHandler::readyRead()
{
    QDataStream in(connection);
    in.setVersion(TPSNetProtocolDef::PROTOCOL_VER);

    if (blockSize == 0)
    {
        if (connection->bytesAvailable() < sizeof(qint16))
        {
            qDebug() << "ClientNetworkHandler::bytes avail < size(qint16)";
            return;
        }

        in >> blockSize;
        qDebug() << "Read in block size of " << blockSize;
    }

    if (connection->bytesAvailable() < blockSize)
    {
        qDebug() << "ClientNetworkHandler::bytes avail < blocksize("
                 << blockSize << "), finished";
        return;
    }

    // Parse the response
    NetResponse response;

    try {
        in >> response;
    } catch (NetMessage::BadRequestException* e) {
        qDebug() << e->what();
        connection->abort();
        return;
    }

    if (response.getResponseCode() < 1)
    {
        emit serverError(response.getRequestId(), response.getResponseCode());
        qDebug() << "Server responded with error " << response.getResponseCode()
                 << " for request " << response.getRequestId();
        blockSize = 0;
        return;
    }

    qDebug() << "ClientNetworkHandler reading reponse for "
             << "invocation: " << response.getInvocation()
             << ", requestId: " << response.getRequestId()
             << ", sessionId: " << response.getSessionId()
             << ", responseCode: " << response.getResponseCode();

    switch (response.getInvocation()) {

    case IAddBook:
    case IAddChapter:
    case IAddSection:
    case IAddCourse:
    case IAddUser:
    case IBanUser:
    case IRmBook:
    case IRmChapter:
    case IRmSection:
    case IBookLink:
    case IBookUnlink:
    {
        QDataStream in(response.getData(), QIODevice::ReadOnly);

        qint32 id;
        in >> id;

        qDebug() << "emitting update completed evt. id=" << id;
        emit updateCompleted(response.getRequestId(),
                             (int)response.getResponseCode(),
                             response.getInvocation(),
                             id);
        break;
    }

    case IGetAllBooks:
    case IGetBookDetails: {
        QDataStream in(response.getData(), QIODevice::ReadOnly);

        qint32 numBooks;
        in >> numBooks;

        if (numBooks > 1 || response.getInvocation() == IGetAllBooks) {
            QList<Textbook*>* bList = new QList<Textbook*>();

            while (numBooks > 0) {
                Textbook* book = new Textbook();
                in >> *book;
                bList->append(book);
                numBooks--;
            }

            emit textbookListReceived(response.getRequestId(),
                                         response.getResponseCode(),
                                         bList);
        } else if (numBooks == 1) {
            Textbook* book = new Textbook();
            in >> *book;

            emit textbookReceived(response.getRequestId(),
                                  response.getResponseCode(),
                                  book);
        }

        break;
    }

    case IGetRequiredBooks: {
        QDataStream in(response.getData(), QIODevice::ReadOnly);

        QMap<Course*, QList<Textbook*>*>* cmap = new QMap<Course*, QList<Textbook*>*>();

        qint32 numCourses;
        in >> numCourses;

        while (numCourses > 0) {
            QList<Textbook*>* tbList = new QList<Textbook*>();
            Course* c = new Course();
            in >> *c;

            qint32 numBooks;
            in >> numBooks;

            while (numBooks > 0) {
                Textbook* book = new Textbook();
                in >> *book;
                tbList->append(book);
                numBooks--;
            }

            cmap->insert(c, tbList);

            numCourses--;
        }

        emit requiredBooksReceived(response.getRequestId(),
                                   response.getResponseCode(),
                                   cmap);

        break;
    }

    case IGetAllCourses: {
        QList<Course*>* clist = new QList<Course*>();
        qint32 count;
        in >> count;

        while (count > 0) {
            Course* c = new Course();
            in >> *c;
            clist->append(c);
            count--;
        }

        emit courseListReceived(response.getRequestId(),
                                response.getResponseCode(),
                                clist);
        break;
    }


    case ILogin: {
        QDataStream in(response.getData(), QIODevice::ReadOnly);

        qint8 roleId; // TODO: check the actual size being writted for this int
        in >> roleId;

        qDebug() << "ClientNetworkHandler::Ready read Login, read role id: " << roleId;

       if (response.getResponseCode() < 1) {
            qDebug() << "ClientNetworkHandler::Login failed for request "
                     << response.getRequestId();
            emit loginFailed(response.getRequestId());
            loggedIn = false;
        } else {
            qDebug() << "ClientNetworkHandler::Login successful for request "
                     << response.getRequestId();
            emit loginSuccessful(response.getRequestId(), (Role)roleId);
            loggedIn = true;
        }

        break;
    }

    case ISubmitOrder: {
        emit orderStatusReceived(response.getRequestId(), response.getResponseCode());
        break;
    }

    case IGenerateReport: {
        break;
    }

    case IGoodbye:
    default:
        this->disconnectFromServer();
        break;
    }

    blockSize = 0;
}

void ClientNetworkHandler::aboutToClose()
{

}

void ClientNetworkHandler::error(QAbstractSocket::SocketError e)
{
    qDebug() << "socket error: " << e;
    emit networkError(e);
}



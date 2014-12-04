#include "ClientNetworkHandler.h"

#include <QString>
#include <QVector>
#include <QDebug>
#include <iostream>

#include "Entity/NetRequest.h"
#include "Entity/NetResponse.h"

#include "Defines.h"
#include "Utils.h"


#define ASSERT_VALID                                                    \
    if (!isValid())                                                     \
    {                                                                   \
        qDebug() << "error: invocation attempt on invalid socket";      \
        return QUuid();                                                 \
    }                                                                   \

using namespace TPSNetProtocolDefs;

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
    request.setInvocation(Login);
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

QUuid ClientNetworkHandler::getRequiredBooks(QString &username)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(GetRequiredBooks);
    request.setRequestId(requestId);

    QByteArray data;
    QDataStream outDataStream(&data, QIODevice::WriteOnly);

    outDataStream << username;

    request.setData(data);

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
    request.setInvocation(GetBookDetails);
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

QUuid ClientNetworkHandler::submitOrder(Order& order)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    NetRequest request;
    request.setInvocation(SubmitOrder);
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
    request.setInvocation(AddCourse);
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
    request.setInvocation(AddBook);
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

QTcpSocket::SocketState ClientNetworkHandler::getSocketState() const
{
    return connection->state();
}

bool ClientNetworkHandler::isConnected() const
{
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
    in.setVersion(TPSNetProtocolDefs::PROTOCOL_VER);

    if (blockSize == 0)
    {
        if (connection->bytesAvailable() < sizeof(qint16))
        {
            return;
        }

        in >> blockSize;
    }

    if (connection->bytesAvailable() < blockSize)
    {
        return;
    }

//    // Validate message by magic number.
//    qint32 mMagic;
//    in >> mMagic;

//    if (mMagic != TPSNetProtocolDefs::PROTOCOL_MAGIC)
//    {
//        qDebug() << "protocol ver mismatch: got magic " << mMagic;
//        this->disconnect();
//        return; // TODO: throw an exception instead
//    }

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

    case AddBook: {
        qDebug() << "emitting update completed evt";
        emit updateCompleted(response.getInvocation(),
                             response.getRequestId(),
                             (int)response.getResponseCode());
        break;
    }

    case AddCourse: {
        qDebug() << "emitting update completed evt";
        emit updateCompleted(response.getInvocation(),
                             response.getRequestId(),
                             response.getResponseCode());
        break;
    }

    case GetBookDetails: {
        QDataStream in(response.getData(), QIODevice::ReadOnly);

        qint32 numBooks;
        in >> numBooks;

        QVector<Textbook*>* vec = new QVector<Textbook*>();

        for (int i = 0; i < numBooks; ++i)
        {
            Textbook* book = new Textbook();
            in >> *book;
            vec->append(book);
        }

        emit textbookDetailsReceived(response.getRequestId(),
                                     response.getResponseCode(),
                                     vec);
        break;
    }

    case GetRequiredBooks: {
        QDataStream in(response.getData(), QIODevice::ReadOnly);

        qint32 numBooks;
        in >> numBooks;

        QVector<qint32>* vec = new QVector<qint32>();

        for (int i = 0; i < numBooks; ++i)
        {
            qint32 id;
            in >> id;
            vec->append(id);
        }

        emit textbookLookupCompleted(response.getRequestId(),
                                     response.getResponseCode(),
                                     vec);
        break;
    }

    case Login: {
        emit loginSuccessful(response.getRequestId());
        loggedIn = true;
        break;
    }

    case SubmitOrder: {
        emit orderStatusReceived(response.getRequestId(), response.getResponseCode());
        break;
    }

    case Goodbye:
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



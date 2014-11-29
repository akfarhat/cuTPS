#include "ClientNetworkHandler.h"

#include <QString>
#include <QVector>
#include <QDebug>
#include <iostream>

#include "TPSNetUtils.h"
#include "Defines.h"
#include "Utils.h"

#define ASSERT_VALID \
    if (!isValid()) \
    {               \
        qDebug() << "error: invocation attempt on invalid socket";\
        return QUuid(); \
    } \

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
        // TODO: Throw an exception
        return QUuid(); // null QUuid
    }

    QUuid requestId = QUuid::createUuid();

    TPSNetProtocol::NetRequest request;
    request.invocation = TPSConstants::Login;
    request.requestId = requestId;

    QByteArray* data = new QByteArray(); // TODO: Manage memory
    QDataStream outDataStream(data, QIODevice::WriteOnly);

    outDataStream << credentials.username << credentials.password;

    request.data = data;

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    TPSNetUtils::SerializeRequest(&outStream, &request);

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::getRequiredBooks(QString &username)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    TPSNetProtocol::NetRequest request;
    request.invocation = TPSConstants::GetRequiredBooks;
    request.requestId = requestId;

    QByteArray* data = new QByteArray(); // TODO: Manage memory
    QDataStream outDataStream(data, QIODevice::WriteOnly);

    outDataStream << username;

    request.data = data;

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    TPSNetUtils::SerializeRequest(&outStream, &request);

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::getBookDetails(Textbook& text)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    TPSNetProtocol::NetRequest request;
    request.invocation = TPSConstants::GetBookDetails;
    request.requestId = requestId;

    QByteArray* data = new QByteArray(); // TODO: Manage memory
    QDataStream outDataStream(data, QIODevice::WriteOnly);

    TPSNetUtils::SerializeTextbook(&outDataStream, &text);

    qDebug() << "forming request with textbook id = " << text.getId();
    outDataStream << text.getId();

    request.data = data;

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    TPSNetUtils::SerializeRequest(&outStream, &request);

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::submitOrder(Order& order)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    TPSNetProtocol::NetRequest request;
    request.invocation = TPSConstants::SubmitOrder;
    request.requestId = requestId;

    QByteArray* data = new QByteArray(); // TODO: Manage memory
    QDataStream outDataStream(data, QIODevice::WriteOnly);

    TPSNetUtils::SerializeOrder(&outDataStream, &order);

    request.data = data;

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    TPSNetUtils::SerializeRequest(&outStream, &request);

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::addCourse(Course& course)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    TPSNetProtocol::NetRequest request;
    request.invocation = TPSConstants::AddCourse;
    request.requestId = requestId;

    QByteArray* data = new QByteArray(); // TODO: Manage memory
    QDataStream outDataStream(data, QIODevice::WriteOnly);

    TPSNetUtils::SerializeCourse(&outDataStream, &course);

    request.data = data;

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    qDebug() << "ClientNetworkHandler::addCourse serializing course";

    TPSNetUtils::SerializeRequest(&outStream, &request);

    qDebug() << "ClientNetworkHandler::addCourse writing payload to network";

    connection->write(requestBytes);

    return requestId;
}

QUuid ClientNetworkHandler::addBook(Textbook& text)
{
    ASSERT_VALID

    QUuid requestId = QUuid::createUuid();

    TPSNetProtocol::NetRequest request;
    request.invocation = TPSConstants::AddBook;
    request.requestId = requestId;

    QByteArray* data = new QByteArray(); // TODO: Manage memory
    QDataStream outDataStream(data, QIODevice::WriteOnly);

    qDebug() << "ClientNetworkHandler::addBook serializing book";

    TPSNetUtils::SerializeTextbook(&outDataStream, &text);

    qDebug() << "ClientNetworkHandler::addBook finished serializing book";

    request.data = data;

    QByteArray requestBytes;
    QDataStream outStream(&requestBytes, QIODevice::WriteOnly);

    qDebug() << "ClientNetworkHandler::addBook serializing request invocation type: "
             << request.invocation;

    TPSNetUtils::SerializeRequest(&outStream, &request);

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
    qDebug() << "READ";

    QDataStream in(connection);
    in.setVersion(TPSConstants::PROTOCOL_VER);

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

    // Parse the block.

    TPSNetProtocol::NetResponse response;

    // Calculate data block size
    qint16 dataBlockSize = blockSize - (2*sizeof(qint8)) - (2*sizeof(QUuid));
    // Allocate ByteArray of that size
    QByteArray* dataBlock = new QByteArray(); // TODO: manage memory
    dataBlock->resize(dataBlockSize);

    response.data = dataBlock;

    TPSNetUtils::DeserializeResponse(&response, &in);

    // For login: read response, emit appropriatge signal.

    if (response.responseCode < 1)
    {
        emit serverError(response.requestId, response.responseCode);
        qDebug() << "Login failed for request " << response.requestId << " with code "
                 << response.responseCode;
    }

    qDebug() << "ClientNetworkHandler reading reponse for "
             << "invocation: " << response.invocation
             << ", requestId: " << response.requestId
             << ", sessionId: " << response.sessionId
             << ", responseCode: " << response.responseCode;

    switch (response.invocation) {

    case TPSConstants::AddBook: {
        emit updateCompleted(response.invocation, response.requestId, response.responseCode);
        qDebug() << "Server responded: book added. Request=" << response.requestId
                 << " Code=" << response.responseCode;
        break;
    }

    case TPSConstants::AddCourse: {
        emit updateCompleted(response.invocation, response.requestId, response.responseCode);
        qDebug() << "Server responded: course added. Request=" << response.requestId
                 << " Code=" << response.responseCode;
        break;
    }

    case TPSConstants::GetBookDetails: {
        Textbook* book = new Textbook(); // TOOD: Manage memory
        QDataStream in(dataBlock, QIODevice::ReadOnly);

        TPSNetUtils::DeserializeTextbook(book, &in);

        emit textbookDetailsReceived(response.requestId, response.responseCode, book);
        qDebug() << "Server responded: book details received. Request=" << response.requestId
                 << " Code=" << response.responseCode
                 << " Book_Id=" << book->getId();
        break;
    }

    case TPSConstants::GetRequiredBooks: {
        QVector<Textbook*>* vector = new QVector<Textbook*>(); // TODO: Manage memory
        QDataStream in(dataBlock, QIODevice::ReadOnly);
        qint32 numBooks;
        in >> numBooks;

        for (int i = 0; i < numBooks; ++i)
        {
            Textbook* book = new Textbook();
            vector->append(book);
            TPSNetUtils::DeserializeTextbook(book, &in);
        }

        qDebug() << "Server responded: "
                 << vector->size()
                 << " required books received. Request="
                 << response.requestId
                 << " Code=" << response.responseCode;
        emit textbookLookupCompleted(response.requestId, response.responseCode, vector);
        break;
    }

    case TPSConstants::Login: {

        QDataStream in(dataBlock, QIODevice::ReadOnly);
        qint8 roleId; // TODO: check the actual size being writted for this int
        in >> roleId;

        qDebug() << "ClientNetworkHandler::Ready read Login, read role id: " << roleId;

        if (response.responseCode < 1) {
            qDebug() << "ClientNetworkHandler::Login failed for request "
                     << response.requestId;
            emit loginFailed(response.requestId);
            loggedIn = false;
        } else {
            qDebug() << "ClientNetworkHandler::Login successful for request "
                     << response.requestId;
            emit loginSuccessful(response.requestId, (Role)roleId);
            loggedIn = true;
        }

        break;
    }

    case TPSConstants::SubmitOrder: {
        qDebug() << "Server responded: order status update. Request=" << response.requestId
                 << " Code=" << response.responseCode;
        emit orderStatusReceived(response.requestId, response.responseCode);
        break;
    }

    case TPSConstants::Goodbye:
    default:
        // TODO: Disconnect from svr.
        loggedIn = false;
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



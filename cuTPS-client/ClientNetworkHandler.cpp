#include "ClientNetworkHandler.h"
#include <QString>
#include <QDebug>


/*
#define ASSERT_VALID \
    if (!isValid()) \
    {               \
        qDebug() << "error: invocation attempt on invalid socket"; \
        return null; \
    } \
*/

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

    delete connection;
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
        connection->close();
    }

    loggedIn = false;
    session.sessionID = -1;
    session.username = "";
}

QUuid ClientNetworkHandler::login(UserCredentials& credentials)
{

    if (!isValid())
    {
        qDebug() << "error: invocation attempt on invalid socket";
        // TODO: Throw an exception
        return QUuid(); // null QUuid
    }

    QUuid requestId = QUuid::createUuid();

    QDataStream out(connection);
    out.setVersion(QDataStream::Qt_4_7);

    out << Login << requestId << credentials.username <<
           credentials.password;

    connection->flush();

    return requestId;
}

QUuid ClientNetworkHandler::getRequiredBooks()
{

}

QUuid ClientNetworkHandler::getBookDetails(Textbook&)
{

}

QUuid ClientNetworkHandler::submitOrder(Order&)
{

}

QUuid ClientNetworkHandler::addCourse(Course&)
{

}

QUuid ClientNetworkHandler::addBook(Textbook&)
{

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

}

void ClientNetworkHandler::aboutToClose()
{

}

void ClientNetworkHandler::error(QAbstractSocket::SocketError e)
{
    qDebug() << "socket error: " << e;
    emit networkError(e);
}



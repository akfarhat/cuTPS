// Name: Defines
// Description:
//     A header containing namespace definitions


#ifndef DEFINES_H
#define DEFINES_H

#include <QDataStream>
#include <QByteArray>
#include <QUuid>

namespace TPSConstants {

enum InvocationDescriptor {
    Login,
    GetRequiredBooks,
    GetBookDetails,
    SubmitOrder,
    AddCourse,
    AddBook,
    Goodbye
};

static const QDataStream::Version PROTOCOL_VER = QDataStream::Qt_4_8;
static const int PORT = 10001;

}

namespace TPSNetProtocol {

struct NetRequest {
    TPSConstants::InvocationDescriptor invocation;
    QUuid requestId;
    QByteArray* data;
};

struct NetResponse {
    qint16 blockSize;
    TPSConstants::InvocationDescriptor invocation;
    QUuid requestId;
    QByteArray* data;
    QUuid sessionId;
    qint8 responseCode;
};

}

#endif // DEFINES_H

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

static const QString PREF_DB_DEFAULT_PATH = "db/cutpsd.db";
static const QString PREF_DB_PATH_SEC = "Database/Database_Path";

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

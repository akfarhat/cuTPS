// Name: Defines
// Description:
//     A header containing namespace definitions


#ifndef DEFINES_H
#define DEFINES_H

#include <QDataStream>
#include <QByteArray>
#include <QUuid>

namespace TPSConstants {

static const QString PREF_DB_PATH_SEC = "Database/Database_Path";

}

namespace TPSNetProtocolDefs {

static const QDataStream::Version PROTOCOL_VER = QDataStream::Qt_4_8;
static const qint32 PROTOCOL_MAGIC = 0xDEADBEEF;
static const int PORT = 10001;

enum InvocationDescriptor {
    Login,
    GetRequiredBooks,
    GetBookDetails,
    SubmitOrder,
    AddCourse,
    AddBook,
    Goodbye
};

}

#endif // DEFINES_H

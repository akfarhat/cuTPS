// Name: Defines
// Description:
//     A header containing namespace definitions

#ifndef DEFINES_H
#define DEFINES_H

#include "libcutps_global.h"

#include <QDataStream>
#include <QUuid>
#include <QString>

namespace TPSNetProtocolDef {

static const QDataStream::Version PROTOCOL_VER = QDataStream::Qt_4_8;
static const qint32 PROTOCOL_MAGIC = 0xDEADBEEF;

enum InvocationDescriptor {
    ILogin,
    IGetRequiredBooks,
    IGetBookDetails,
    IGetAllCourses,
    ISubmitOrder,
    IAddCourse,
    IAddBook,
    IAddChapter,
    IAddSection,
    IRmBook,
    IRmChapter,
    IRmSection,
    IRmCourse,
    IBookLink,
    IBookUnlink,
    IGenerateReport,
    IGetAllBooks,
    IAddUser,
    IBanUser,
    IGoodbye
};

}

namespace TPSDef {

enum ResponseCode {
    Fail,
    Success
};

enum Role {
    Anonymous,
    StudentUser,
    ContentManagerUser,
    AdministratorUser,
    SuperUser
};

// Information returned by the server for requests
struct ServerResponse {
    QUuid sessionID;
    ResponseCode code;
    QString message;
};

// For user authentication
struct UserCredentials {
    QString username;
    QString password;
};

// For session identification
struct SessionCredentials {
    QString username;
    int sessionID;
};

}

#endif // DEFINES_H

// Name: Utils
// Description:
//     A utilities header, defining various enumerations
//     and structs that are used in the networking protocol
//     and in session identification


#ifndef UTILS_H
#define UTILS_H

#include "libcutps_global.h"

#include <QString>
#include <QDataStream>
#include <QUuid>

#include "Defines.h"

// A pass/fail response for a test case
enum LIBCUTPS_EXPORT ResponseCode {
    Fail,
    Success
};

enum LIBCUTPS_EXPORT Role {
    None,
    Student,
    ContentManager
};

// Information returned by the server for requests
struct LIBCUTPS_EXPORT ServerResponse {
    QUuid sessionID;
    ResponseCode code;
    QString message;
};

// For user authentication
struct LIBCUTPS_EXPORT UserCredentials {
    QString username;
    QString password;
};

// For session identification
struct LIBCUTPS_EXPORT SessionCredentials {
    QString username;
    int sessionID;
};


#endif // UTILS_H

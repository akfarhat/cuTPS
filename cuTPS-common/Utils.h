// Name: Utils
// Description:
//     A utilities header, defining various enumerations
//     and structs that are used in the networking protocol
//     and in session identification


#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QDataStream>
#include <QUuid>

#include "Defines.h"

// A pass/fail response for a test case
enum ResponseCode {
    Success,
    Fail
};

// Information returned by the server for requests
struct ServerResponse {
    QUuid sessionID;
    qint8 errorCode;
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

namespace TPSNetUtils {

static void SerializeRequest(QDataStream* dest, const TPSNetProtocol::NetRequest* src);
static void SerializeResponse(QDataStream* dest, const TPSNetProtocol::NetResponse* src);
static void DeserializeRequest(TPSNetProtocol::NetRequest* dest, QDataStream* src);
static void DeserializeResponse(TPSNetProtocol::NetResponse* dest, QDataStream* src);

}


#endif // UTILS_H

#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QByteArray>
#include <QUuid>

#include "Defines.h"

enum ResponseCode {
    Success,
    Fail
};

struct ServerResponse {
    QUuid sessionID;
    quint8 errorCode;
};

struct UserCredentials {
    QString username;
    QString password;
};

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

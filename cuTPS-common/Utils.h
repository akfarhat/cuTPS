#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QUuid>

enum ResponseCode {
    Success,
    Fail
};

struct ServerResponse {
    QUuid sessionID;
    ResponseCode code;
    QString message;
};

struct UserCredentials {
    QString username;
    QString password;
};

struct SessionCredentials {
    QString username;
    int sessionID;
};

#endif // UTILS_H

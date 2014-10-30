#ifndef UTILS_H
#define UTILS_H

#include <QString>

struct ServerResponse {
    int session_id;
    int code;

};

struct UserCredentials {
    QString username;
    QString password;
};

struct SessionCredentials {
    QString username;
    int session_id;
};

#endif // UTILS_H

#ifndef UTILS_H
#define UTILS_H

struct ServerResponse {
    int session_id;
    int code;

};

struct UserCredentials {
    QString username;
    QString password;
};

#endif // UTILS_H

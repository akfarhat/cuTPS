#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QUuid>

enum ResponseCode {
    Success,
    Fail
};

enum InvocationDescriptor {
    Login,
    GetRequiredBooks,
    GetBookDetails,
    SubmitOrder,
    AddCourse,
    AddBook,
    Goodbye
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

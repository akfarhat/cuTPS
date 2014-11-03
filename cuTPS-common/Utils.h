// Name: Utils
// Description:
//     A utilities header, defining various enumerations
//     and structs that are used in the networking protocol
//     and in session identification


#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QUuid>

// A pass/fail response for a test case
enum ResponseCode {
    Success,
    Fail
};

// Headers in the protocol, representing
// message types for requests and responses
enum InvocationDescriptor {
    Login,
    GetRequiredBooks,
    GetBookDetails,
    SubmitOrder,
    AddCourse,
    AddBook,
    Goodbye
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

#endif // UTILS_H

// Name: Defines
// Description:
//     A header containing namespace definitions

#ifndef DEFINES_H
#define DEFINES_H

#include "libcutps_global.h"

#include <QDataStream>

namespace TPSNetProtocolDefs {

static const QDataStream::Version PROTOCOL_VER = QDataStream::Qt_4_8;
static const qint32 PROTOCOL_MAGIC = 0xDEADBEEF;

enum InvocationDescriptor {
    Login,
    GetRequiredBooks,
    GetBookDetails,
    SubmitOrder,
    AddCourse,
    AddBook,
    GenerateReport,
    Goodbye
};

enum UsrPermissionGroup {
    UsrStu,
    UsrCm,
    UsrAdm,
    UsrAnonymous,
    UsrSuperuser
};

}

#endif // DEFINES_H

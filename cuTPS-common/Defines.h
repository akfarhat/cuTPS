// Name: Defines
// Description:
//     A header containing namespace definitions


#ifndef DEFINES_H
#define DEFINES_H

#include "libcutps_global.h"

#include <QDataStream>

namespace TPSNetProtocolDefs {

LIBCUTPS_EXPORT static const QDataStream::Version PROTOCOL_VER = QDataStream::Qt_4_8;
LIBCUTPS_EXPORT static const qint32 PROTOCOL_MAGIC = 0xDEADBEEF;

enum LIBCUTPS_EXPORT InvocationDescriptor {
    Login,
    GetRequiredBooks,
    GetBookDetails,
    SubmitOrder,
    AddCourse,
    AddBook,
    GenerateReport,
    Goodbye
};

enum LIBCUTPS_EXPORT UsrPermissionGroup {
    UsrStu,
    UsrCm,
    UsrAdm,
    UsrNobody
};

}

#endif // DEFINES_H

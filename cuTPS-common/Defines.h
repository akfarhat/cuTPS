// Name: Defines
// Description:
//     A header containing namespace definitions


#ifndef DEFINES_H
#define DEFINES_H

#include <QDataStream>
#include <QByteArray>
#include <QUuid>
#include <QMap>

namespace TPSConstants {

static const QString PREF_DB_PATH_SEC   = "Database/Database_Path";

static const QString PREF_PORT          = "Network/Port";
static const int     PREF_PORT_DEF      = 12754;

static const QString PREF_MAX_THR       = "Network/Max_Threads";
static const int     PREF_MAX_THR_DEF   = 15;

}

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
    UsrNobody
};

}

#endif // DEFINES_H

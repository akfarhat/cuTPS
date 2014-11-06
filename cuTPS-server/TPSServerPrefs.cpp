#include "TPSServerPrefs.h"
#include "Defines.h"

#include <QSettings>
#include <QDir>

TPSServerPrefs::TPSServerPrefs()
{
}

QString TPSServerPrefs::GetDbPath()
{
    QSettings settings("cutpsd.conf", QSettings::IniFormat);
    QString dbPath = settings.value(TPSConstants::PREF_DB_PATH_SEC, QDir::currentPath() + QString("/db/cutpsd.db")).toString();
    settings.setValue(TPSConstants::PREF_DB_PATH_SEC, dbPath);
    return dbPath;
}

//QString TPSServerPrefs::GetServerAddr()
//{
//    QSettings setting("cutpsd.conf", QSettings::IniFormat);
//    QString serverAddr = settings.value(TPSConstants::PREF_ADDR, TPSConstants::PREF_DEFAULT_ADDR).toString();
//    settings.setValue(TPSConstants::PREF_ADDR, serverAddr);
//    return serverAddr;
//}

//int TPSServerPrefs::GetPort()
//{
//    QSettings setting("cutpsd.conf", QSettings::IniFormat);
//    int port = settings.value(TPSConstants::PREF_PORT, TPSConstants::PREF_DEFAULT_PORT).toString();
//    settings.setValue(TPSConstants::PREF_PORT, serverAddr);
//    return port;
//}

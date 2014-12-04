#include "ServerPrefs.h"
#include "Defines.h"

#include <QSettings>
#include <QDir>

ServerPrefs::ServerPrefs()
{
}

const QString ServerPrefs::GetDbPath()
{
    QSettings settings("cutpsd.conf", QSettings::IniFormat);
    const QString dbPath = settings.value(TPSConstants::PREF_DB_PATH_SEC, QDir::currentPath() + QString("/db/cutpsd.db")).toString();
    settings.setValue(TPSConstants::PREF_DB_PATH_SEC, dbPath);
    return dbPath;
}

int ServerPrefs::GetPort()
{
    QSettings settings("cutpsd.conf", QSettings::IniFormat);
    const int port = settings.value(TPSConstants::PREF_PORT, TPSConstants::PREF_PORT_DEF).toInt();
    settings.setValue(TPSConstants::PREF_PORT, port);
    return port;
}

int ServerPrefs::MaxThreads()
{
    QSettings settings("cutpsd.conf", QSettings::IniFormat);
    const int nThreads = settings.value(TPSConstants::PREF_MAX_THR, TPSConstants::PREF_MAX_THR_DEF).toInt();
    settings.setValue(TPSConstants::PREF_MAX_THR, nThreads);
    return nThreads;
}

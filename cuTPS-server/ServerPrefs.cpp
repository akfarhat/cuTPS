#include "ServerPrefs.h"
#include "Defines.h"

#include <QSettings>
#include <QDir>

using namespace TPSPrefDef;

ServerPrefs::ServerPrefs()
{
}

const QString ServerPrefs::GetDbPath()
{
    QSettings settings(PREF_CONF_FILE, QSettings::IniFormat);
    const QString dbPath = settings.value(PREF_DB_PATH_SEC, QDir::currentPath() + QString("/db/cutpsd.db")).toString();
    settings.setValue(PREF_DB_PATH_SEC, dbPath);
    return dbPath;
}

int ServerPrefs::GetPort()
{
    QSettings settings(PREF_CONF_FILE, QSettings::IniFormat);
    const int port = settings.value(PREF_PORT, PREF_PORT_DEF).toInt();
    settings.setValue(PREF_PORT, port);
    return port;
}

int ServerPrefs::MaxThreads()
{
    QSettings settings(PREF_CONF_FILE, QSettings::IniFormat);
    const int nThreads = settings.value(PREF_MAX_THR, PREF_MAX_THR_DEF).toInt();
    settings.setValue(PREF_MAX_THR, nThreads);
    return nThreads;
}

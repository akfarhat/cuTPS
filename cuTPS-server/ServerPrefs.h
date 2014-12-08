#ifndef TPSSERVERPREFS_H
#define TPSSERVERPREFS_H

#include <QString>

class ServerPrefs
{
public:
    ServerPrefs();

    static const QString GetDbPath();
    static int GetPort();
    static int MaxThreads();

};

namespace TPSPrefDef
{

static const QString PREF_CONF_FILE     = "cutpsd.conf";

static const QString PREF_DB_PATH_SEC   = "Database/Database_Path";

static const QString PREF_PORT          = "Network/Port";
static const int     PREF_PORT_DEF      = 12754;

static const QString PREF_MAX_THR       = "Network/Max_Threads";
static const int     PREF_MAX_THR_DEF   = 15;

}

#endif // TPSSERVERPREFS_H

#ifndef TPSSERVERPREFS_H
#define TPSSERVERPREFS_H

#include <QString>

class ServerPrefs
{
public:
    ServerPrefs();

    static QString GetDbPath();
    static QString GetServerAddr();
    static int GetPort();
};

#endif // TPSSERVERPREFS_H

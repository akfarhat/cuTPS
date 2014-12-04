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

#endif // TPSSERVERPREFS_H

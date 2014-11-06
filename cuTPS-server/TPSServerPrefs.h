#ifndef TPSSERVERPREFS_H
#define TPSSERVERPREFS_H

#include <QString>

class TPSServerPrefs
{



public:
    TPSServerPrefs();

    static QString GetDbPath();
    static QString GetServerAddr();
    static int GetPort();
};

#endif // TPSSERVERPREFS_H

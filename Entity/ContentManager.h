#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include "User.h"
#include <QString>
using namespace std;

class ContentManager: public User {

    private:
        QString emailAddress;

    public:
        ContentManager(QString, QString);
        ~ContentManager();
        QString getEmailAddress();

        QString getType();
};

#endif // CONTENTMANAGER_H

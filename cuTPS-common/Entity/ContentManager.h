// Class: ContentManager
// Type: Entity
// Description:
//     Represents the type of user that can modify
//     content available in the system


#ifndef CONTENTMANAGER_H
#define CONTENTMANAGER_H

#include "libcutps_global.h"

#include <QString>

#include "User.h"

class LIBCUTPS_EXPORT ContentManager : public User {

    private:
        QString emailAddress;

    public:
        ContentManager(qint32, QString, QString);
        ~ContentManager();

        QString getEmailAddress();
        void setEmailAddress(QString);

        QString getDetails();
};

#endif // CONTENTMANAGER_H

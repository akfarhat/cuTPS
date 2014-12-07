// Class: User
// Type: Entity
// Description:
//     Abstract class representing commonalities for
//     a user in the cuTPS system


#ifndef USER_H
#define USER_H

#include "libcutps_global.h"

#include <QString>

#include "Defines.h"

using namespace TPSDef;

class LIBCUTPS_EXPORT User
{
public:
    User(QString name="<NO_NAME>", QString uname="alpine");
    User(qint32 id, QString name, QString uname);
    ~User();

    qint32 getUserId();
    void setUserId(qint32);

    QString getUsername();
    void setUsername(QString);

    QString getName();
    void setName(QString);

    virtual QString getDetails();

    Role getRole() const;
    void setRole(const Role value);

private:
    qint32 userId;
    QString name;
    QString username;
    Role role = None;
};

#endif // USER_H

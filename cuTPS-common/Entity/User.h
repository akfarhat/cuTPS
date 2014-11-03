// Class: User
// Type: Entity
// Description:
//     Abstract class representing commonalities for
//     a user in the cuTPS system


#ifndef USER_H
#define USER_H

#include <QString>
using namespace std;


class User {

    private:
        int userId;
        QString name;
        QString username;

    public:
        User(QString, QString);
        ~User();
        int getUserId();
        QString getUsername();
        QString getName();

        virtual QString getType() = 0;
};

#endif // USER_H

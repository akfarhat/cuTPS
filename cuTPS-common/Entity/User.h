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
        User(int, QString, QString);
        ~User();
        int getUserId();
        void setUserId(int);

        QString getUsername();
        void setUsername(QString);

        QString getName();
        void setName(QString);

        virtual QString getDetails() = 0;
};

#endif // USER_H

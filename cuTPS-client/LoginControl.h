#ifndef LOGINCONTROL_H
#define LOGINCONTROL_H

#include "Utils.h"
#include "ClientNetworkHandler.h"

class LoginControl {

    private:
        ClientNetworkHandler network;

    public:
        LoginControl();
        ~LoginControl();

        QUuid login(UserCredentials&);


};

#endif // LOGINCONTROL_H

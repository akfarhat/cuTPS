// Class: LoginControl
// Type: Control
// Description:
//     This class is responsible for requesting session
//     credentials for the client use

#ifndef LOGINCONTROL_H
#define LOGINCONTROL_H

#include "Utils.h"
#include "ClientNetworkHandler.h"

class LoginControl {

    private:
        ClientNetworkHandler &network;

    public:
        LoginControl(ClientNetworkHandler &);
        ~LoginControl();

        // Request a login for this user
        QUuid login(UserCredentials&);

};

#endif // LOGINCONTROL_H
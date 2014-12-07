// Class: LoginControl
// Type: Control
// Description:
//     This class is responsible for requesting session
//     credentials for the client use

#ifndef LOGINCONTROL_H
#define LOGINCONTROL_H

#include "Defines.h"
#include "Login.h"
#include "ClientNetworkHandler.h"
#include "ContentManagementInterface.h"
#include "CartManagementInterface.h"

#include <QObject>

class LoginControl : public QObject
{
    private:
        Q_OBJECT
        Login *loginWin;
        ContentManagementInterface *cmIF;
        CartManagementInterface *studentIF;
        ClientNetworkHandler *network;

    public:
        LoginControl(ClientNetworkHandler *);
        ~LoginControl();

        // Request a login for this user
        void login(QUuid&, UserCredentials&);
        void startSession();

    private slots:
        void loginSuccessful(QUuid, Role);
        void loginFailed(QUuid);
};

#endif // LOGINCONTROL_H

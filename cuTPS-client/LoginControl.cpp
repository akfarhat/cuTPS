#include "LoginControl.h"
#include "ContentManagementInterface.h"

#include <QDebug>

#include "Entity/Chapter.h"
#include "Entity/Section.h"
#include "Entity/CreditCardInfo.h"

LoginControl::LoginControl(ClientNetworkHandler *serverAPI)
    : network(serverAPI)
{
    // Connect handlers for network callbacks on login events
    connect(network, SIGNAL(loginSuccessful(QUuid, Role)),
            this, SLOT(loginSuccessful(QUuid, Role)));

    connect(network, SIGNAL(loginFailed(QUuid)),
            this, SLOT(loginFailed(QUuid)));
}

LoginControl::~LoginControl() {
}

void LoginControl::startSession()
{
    // Create the login window with this as its parent
    loginWin = new Login(0, network, this);

    loginWin->show();
}

void LoginControl::login(QUuid &reqId, UserCredentials &userCreds) {
    reqId = network->login(userCreds);
}

void LoginControl::loginSuccessful(QUuid requestId, Role userRole) {
    qDebug() << "LoginControl::successfulLogin for: " << userRole
             << " - " << requestId;

    // TODO: Need to get user information such as name, etc. from DB to create the user (i.e. Student or ContentManager) object that will be passed around
    switch (userRole) {

        case Role::StudentUser:
          {
            qDebug() << "LoginControl::loginSuccessful creating studentInterface";

            studentIF = new CartManagementInterface(0, network);
            studentIF->show();
            loginWin->close();
            break;
          }

        case Role::ContentManagerUser:
            qDebug() << "LoginControl::loginSuccessful creating cmInterface";

            cmIF = new ContentManagementInterface(0, network);
            cmIF->show();
            loginWin->close(); // Assuming we aren't going to handle logouts..
            break;

        case Role::AdministratorUser:
            qDebug() << "TODO: handle admin login";
            break;
    }
}

void LoginControl::loginFailed(QUuid requestId) {
    qDebug() << "Login::failedLogin for: " << requestId;
}

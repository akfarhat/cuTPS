#include "LoginControl.h"

#include <QDebug>

LoginControl::LoginControl(ClientNetworkHandler *serverAPI)
    : network(serverAPI) {
}

LoginControl::~LoginControl() {
}

void LoginControl::login(QUuid &reqId, UserCredentials &userCreds) {
    reqId = network->login(userCreds);
}

#include "LoginControl.h"

LoginControl::LoginControl(ClientNetworkHandler &serverAPI)
    : network(serverAPI) {}

LoginControl::~LoginControl() {

}

QUuid LoginControl::login(UserCredentials &userCreds) {
    return network.login(userCreds);
}

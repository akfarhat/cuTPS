#include "LoginControl.h"

LoginControl::LoginControl() {

}

LoginControl::~LoginControl() {

}

QUuid LoginControl::login(UserCredentials &userCreds) {
    return network.login(userCreds);
}

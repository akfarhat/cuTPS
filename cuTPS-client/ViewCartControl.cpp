#include "ViewCartControl.h"

ViewCartControl::ViewCartControl(ClientNetworkHandler *netHandler) : network(netHandler) {

    requestAPI = new CartRequestsAPI(0, network);

}

ViewCartControl::~ViewCartControl() {
    delete detailsWindow;
    delete network;
    delete requestAPI;
}

void ViewCartControl::launchCartDetailsWindow() {
    detailsWindow = new CartDetailsWindow(0, this, requestAPI);

    detailsWindow->show();
}


#include "ViewCartControl.h"

ViewCartControl::ViewCartControl(ClientNetworkHandler *netHandler, Student *stu) : network(netHandler), student(stu) {

    requestAPI = new CartRequestsAPI(0, network);

}

ViewCartControl::~ViewCartControl() {
    delete detailsWindow;
    delete network;
    delete requestAPI;
}

Student* ViewCartControl::getStudent() {
    return student;
}

void ViewCartControl::launchCartDetailsWindow() {
    detailsWindow = new CartDetailsWindow(0, this, requestAPI);

    detailsWindow->show();
}


#include "ViewCartControl.h"

ViewCartControl::ViewCartControl(QWidget *parent, ClientNetworkHandler *netHandler, Student *stu) : parentWidget(parent), network(netHandler), student(stu) {

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
    detailsWindow = new CartDetailsWindow(parentWidget, this, requestAPI);

    detailsWindow->show();
}


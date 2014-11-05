#include "ViewRequiredBooksControl.h"

ViewRequiredBooksControl::ViewRequiredBooksControl(ClientNetworkHandler &serverAPI)
    : network(serverAPI) {}

ViewRequiredBooksControl::~ViewRequiredBooksControl() {

}

void ViewRequiredBooksControl::getRequiredBooks(QUuid &reqId, QString& username) {
    reqId = network.getRequiredBooks(username);
}

#include "ViewRequiredBooksControl.h"

ViewRequiredBooksControl::ViewRequiredBooksControl(ClientNetworkHandler &serverAPI)
    : network(serverAPI) {}

ViewRequiredBooksControl::~ViewRequiredBooksControl() {

}

// TODO: Remove 'username' parameter, unused.
void ViewRequiredBooksControl::getRequiredBooks(QUuid &reqId, QString& username) {
    reqId = network.getRequiredBooks();
}

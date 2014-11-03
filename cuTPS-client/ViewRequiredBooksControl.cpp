#include "ViewRequiredBooksControl.h"

ViewRequiredBooksControl::ViewRequiredBooksControl(ClientNetworkHandler &serverAPI)
    : network(serverAPI) {}

ViewRequiredBooksControl::~ViewRequiredBooksControl() {

}

void ViewRequiredBooksControl::getRequiredBooks(QUuid &reqId) {
    reqId = network.getRequiredBooks();
}

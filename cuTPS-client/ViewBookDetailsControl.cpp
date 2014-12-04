#include "ViewBookDetailsControl.h"

ViewBookDetailsControl::ViewBookDetailsControl(ClientNetworkHandler &serverAPI)
    : network(serverAPI) {}

ViewBookDetailsControl::~ViewBookDetailsControl() {

}

void ViewBookDetailsControl::getBookDetails(QUuid &reqId, int id) {
    reqId = network.getBookDetails(id);
}

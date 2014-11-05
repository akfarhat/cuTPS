#include "ViewBookDetailsControl.h"

ViewBookDetailsControl::ViewBookDetailsControl(ClientNetworkHandler &serverAPI)
    : network(serverAPI) {}

ViewBookDetailsControl::~ViewBookDetailsControl() {

}

void ViewBookDetailsControl::getBookDetails(QUuid &reqId, Textbook &book) {
    reqId = network.getBookDetails(book);
}

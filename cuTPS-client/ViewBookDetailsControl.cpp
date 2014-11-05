#include "ViewBookDetailsControl.h"

ViewBookDetailsControl::ViewBookDetailsControl(ClientNetworkHandler &serverAPI)
    : network(serverAPI) {}

ViewBookDetailsControl::~ViewBookDetailsControl() {

}

QUuid ViewBookDetailsControl::getBookDetails(Textbook &book) {
    return network.getBookDetails(book);
}

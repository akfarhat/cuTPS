#include "ViewBookDetailsControl.h"

ViewBookDetailsControl::ViewBookDetailsControl() {

}

ViewBookDetailsControl::~ViewBookDetailsControl() {

}

void ViewBookDetailsControl::getBookDetails(QUuid &reqId, Textbook &book) {
    reqId = network.getBookDetails(book);
}

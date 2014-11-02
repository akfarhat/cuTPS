#include "ViewRequiredBooksControl.h"

ViewRequiredBooksControl::ViewRequiredBooksControl() {

}

ViewRequiredBooksControl::~ViewRequiredBooksControl() {

}

void ViewRequiredBooksControl::getRequiredBooks(QUuid &reqId) {
    reqId = network.getRequiredBooks();
}

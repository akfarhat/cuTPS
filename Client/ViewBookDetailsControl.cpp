#include "ViewBookDetailsControl.h"

ViewBookDetailsControl::ViewBookDetailsControl() {

}

ViewBookDetailsControl::~ViewBookDetailsControl() {

}

void ViewBookDetailsControl::getBookDetails(SessionCredentials *sessionCreds, Textbook *book, ServerResponse *response) {
    response = network.getBookDetails(sessionCreds, book);
}

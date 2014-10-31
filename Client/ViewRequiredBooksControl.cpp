#include "ViewRequiredBooksControl.h"

ViewRequiredBooksControl::ViewRequiredBooksControl() {

}

ViewRequiredBooksControl::~ViewRequiredBooksControl() {

}

void ViewRequiredBooksControl::getRequiredBooks(SessionCredentials *sessionCreds, ServerResponse *response) {
    network.getRequiredBooks(sessionCreds, response);
}

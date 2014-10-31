#include "ViewRequiredBooksControl.h"

ViewRequiredBooksControl::ViewRequiredBooksControl() {

}

ViewRequiredBooksControl::~ViewRequiredBooksControl() {

}

void ViewRequiredBooksControl::getRequiredBooks(SessionCredentials *sessionCreds, ServerResponse *response) {
    response = network.getRequiredBooks(sessionCreds);
}

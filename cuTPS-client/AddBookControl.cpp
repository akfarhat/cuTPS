#include "AddBookControl.h"

AddBookControl::AddBookControl() {

}

AddBookControl::~AddBookControl() {

}

void AddBookControl::addBook(SessionCredentials *sessionCreds, Textbook *newTextbook, ServerResponse *response) {
    network.addBook(sessionCreds, newTextbook, response);
}

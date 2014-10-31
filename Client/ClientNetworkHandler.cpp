#include "ClientNetworkHandler.h"
#include <QString>

ClientNetworkHandler::ClientNetworkHandler() {

}

void ClientNetworkHandler::login(UserCredentials *cred, ServerResponse *res) {
    // TODO: Serialize the data, make the request, read the result, fill out res

    // Dummy data for testing
    res->code = Success;
    res->sessionID = 0;
    res->message = QString("Log in successful");
}

void ClientNetworkHandler::getRequiredBooks(SessionCredentials *cred, ServerResponse *res) {

}

void ClientNetworkHandler::getBookDetails(SessionCredentials *cred, Textbook *text, ServerResponse *res) {

}

void ClientNetworkHandler::submitOrder(SessionCredentials *cred, Order *, ServerResponse *res) {

}

void ClientNetworkHandler::addCourse(SessionCredentials *cred, Course *course, ServerResponse *res) {

}

void ClientNetworkHandler::addBook(SessionCredentials *cred, Textbook * text, ServerResponse *res) {

}

#include "CartRequestsAPI.h"

CartRequestsAPI::CartRequestsAPI(ClientNetworkHandler *net) : network(net) {


}

CartRequestsAPI::~CartRequestsAPI() {

}


QUuid CartRequestsAPI::getRequiredBooks(QString &username) {
    return network->getRequiredBooks(username);
}

QUuid CartRequestsAPI::getBookDetails(Textbook &book) {
    return network->getBookDetails(book);
}

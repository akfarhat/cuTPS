#include "CartRequestsAPI.h"

CartRequestsAPI::CartRequestsAPI(QObject *parent, ClientNetworkHandler *net) : QObject(parent), network(net) {


}

CartRequestsAPI::~CartRequestsAPI() {

}


QUuid CartRequestsAPI::getRequiredBooks(QString &username) {
    return network->getRequiredBooks(username);
}

QUuid CartRequestsAPI::getBookDetails(int bookId) {
    return network->getBookDetails(bookId);
}

#include "CartRequestsAPI.h"

CartRequestsAPI::CartRequestsAPI(QObject *parent, ClientNetworkHandler *netHandler, Student *user) :
    QObject(parent),
    network(netHandler),
    student(user)
{


}

CartRequestsAPI::~CartRequestsAPI()
{

}

ClientNetworkHandler* CartRequestsAPI::getNetwork() {
    return network;
}

Student* CartRequestsAPI::getStudent() {
    return student;
}

QUuid CartRequestsAPI::getRequiredBooks(QString &username)
{
    return network->getRequiredBooks(username);
}


QUuid CartRequestsAPI::getBookDetails(int bookId) {
    return network->getBookDetails(bookId);
}

QUuid CartRequestsAPI::submitOrder(Order &newOrder)
{
    return network->submitOrder(newOrder);
}
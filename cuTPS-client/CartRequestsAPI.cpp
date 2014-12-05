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

QUuid CartRequestsAPI::getBookDetails(Textbook &book)
{
    return network->getBookDetails(book);
}

QUuid CartRequestsAPI::submitOrder(Order &newOrder)
{
    return network->submitOrder(newOrder);
}

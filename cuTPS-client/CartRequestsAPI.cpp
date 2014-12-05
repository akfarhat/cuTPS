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

<<<<<<< HEAD
QUuid CartRequestsAPI::getBookDetails(Textbook &book)
{
    return network->getBookDetails(book);
=======
QUuid CartRequestsAPI::getBookDetails(int bookId) {
    return network->getBookDetails(bookId);
>>>>>>> 92ef426cdc305ae0b9763e59be4edd5fec062368
}

QUuid CartRequestsAPI::submitOrder(Order &newOrder)
{
    return network->submitOrder(newOrder);
}

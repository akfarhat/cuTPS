#ifndef CLIENTNETWORKHANDLER_H
#define CLIENTNETWORKHANDLER_H

#include "Utils.h"
#include "Entity/Textbook.h"
#include "Entity/Order.h"
#include "Entity/Course.h"

// Note, this could inherit from a NetworkHandler
// that manages the networking
class ClientNetworkHandler {

    public:
        ClientNetworkHandler();
        // These methods should serialize the data and
        // send it to the ServerNetworkHandler
        ServerResponse *login(UserCredentials *);
        ServerResponse *getRequiredBooks(SessionCredentials *);
        ServerResponse *getBookDetails(SessionCredentials *, Textbook *);
        ServerResponse *submitOrder(SessionCredentials *, Order *);
        ServerResponse *addCourse(SessionCredentials *, Course *);
        ServerResponse *addBook(SessionCredentials *, Textbook *);
};

#endif // CLIENTNETWORKHANDLER_H

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
        void login(UserCredentials *, ServerResponse *);
        void getRequiredBooks(SessionCredentials *, ServerResponse *);
        void getBookDetails(SessionCredentials *, Textbook *, ServerResponse *);
        void submitOrder(SessionCredentials *, Order *, ServerResponse *);
        void addCourse(SessionCredentials *, Course *, ServerResponse *);
        void addBook(SessionCredentials *, Textbook *, ServerResponse *);
};

#endif // CLIENTNETWORKHANDLER_H

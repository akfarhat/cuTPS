// Class: CartRequestsAPI
// Type: Control
// Description:
//     this class is responsible for invoking cart-related requests to the client network handler.
//
// Traceability: CartRequestsAPI class in the CartManagement subsystem

#ifndef CARTREQUESTSAPI_H
#define CARTREQUESTSAPI_H

#include <QUuid>
#include "ClientNetworkHandler.h"
#include "Entity/Textbook.h"
#include "Entity/Order.h"

class CartRequestsAPI {
    public:
        CartRequestsAPI(ClientNetworkHandler*);
        ~CartRequestsAPI();

        QUuid getRequiredBooks(QString&);
        QUuid getBookDetails(Textbook&);
        QUuid submitOrder(Order&);

    private:
        ClientNetworkHandler *network;


};

#endif // CARTREQUESTSAPI_H

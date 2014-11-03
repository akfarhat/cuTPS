// Class: SubmitOrderControl
// Type: Control
// Description:
//     This class is responsible for invoking the client
//     side API method in the network handler for submitting
//     an order to the server

#ifndef SUBMITORDERCONTROL_H
#define SUBMITORDERCONTROL_H

#include "Utils.h"
#include "ClientNetworkHandler.h"
#include "Entity/Order.h"

class SubmitOrderControl {

    private:
        ClientNetworkHandler &network;

    public:
        SubmitOrderControl(ClientNetworkHandler &);
        ~SubmitOrderControl();

        // Submit the order and return a request identifier
        void submitOrder(QUuid &, Order &);
};

#endif // SUBMITORDERCONTROL_H

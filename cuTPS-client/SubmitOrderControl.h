#ifndef SUBMITORDERCONTROL_H
#define SUBMITORDERCONTROL_H

#include "Utils.h"
#include "ClientNetworkHandler.h"
#include "Entity/Order.h"

class SubmitOrderControl {

    private:
        ClientNetworkHandler network;

    public:
        SubmitOrderControl();
        ~SubmitOrderControl();

        void submitOrder(QUuid &, Order &);
};

#endif // SUBMITORDERCONTROL_H

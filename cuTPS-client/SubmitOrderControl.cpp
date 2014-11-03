#include "SubmitOrderControl.h"

SubmitOrderControl::SubmitOrderControl(ClientNetworkHandler &serverAPI)
    : network(serverAPI) {}

SubmitOrderControl::~SubmitOrderControl() {

}

void SubmitOrderControl::submitOrder(QUuid &reqId, Order &newOrder) {
    reqId = network.submitOrder(newOrder);
}



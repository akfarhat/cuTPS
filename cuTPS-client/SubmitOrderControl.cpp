#include "SubmitOrderControl.h"

SubmitOrderControl::SubmitOrderControl() {

}

SubmitOrderControl::~SubmitOrderControl() {

}

void SubmitOrderControl::submitOrder(QUuid &reqId, Order &newOrder) {
    reqId = network.submitOrder(newOrder);
}



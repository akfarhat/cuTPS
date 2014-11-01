#include "SubmitOrderControl.h"

SubmitOrderControl::SubmitOrderControl() {

}

SubmitOrderControl::~SubmitOrderControl() {

}

void SubmitOrderControl::submitOrder(SessionCredentials *sessionCreds, Order *newOrder, ServerResponse *response) {
    network.submitOrder(sessionCreds, newOrder, response);
}



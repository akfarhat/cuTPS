#include "PlaceOrderControl.h"

#include <QDebug>

PlaceOrderControl::PlaceOrderControl(CartDetailsWindow *window, CartRequestsAPI *api)
    : cartDetailsWindow(window),
      requestAPI(api) {

    QObject::connect(requestAPI->getNetwork(), SIGNAL(orderStatusReceived(QUuid, int)), this, SLOT(orderStatusReceived(QUuid, int)));
}

PlaceOrderControl::~PlaceOrderControl() {

    delete billingWindow;
}

Student* PlaceOrderControl::getStudent() {

    if (requestAPI != NULL)
        return requestAPI->getStudent();

    return NULL;
}

void PlaceOrderControl::launchBillingWindow() {

    billingWindow = new BillingWindow(0, this);

    billingWindow->exec();
}

void PlaceOrderControl::submitOrder() {

    QUuid requestId;

    if (this->getStudent() != NULL) {
        if (!this->getStudent()->getCart()->getItems().empty()) {
            QVector<qint32> itemIds;

            for (SellableItem *item: this->getStudent()->getCart()->getItems()) {
                itemIds.append(item->getId());
            }

            Order newOrder(&itemIds, this->getStudent()->getCreditCardInfo(), this->getStudent()->getDeliveryInfo());

            requestId = requestAPI->submitOrder(newOrder);


            qDebug() << "PlaceOrderControl::submitOrder: Submitted order request with request ID " << requestId << " to the server...";
        }
    }


}

void PlaceOrderControl::orderStatusReceived(QUuid requestId, int responseCode) {

    if (responseCode == ResponseCode::Success) {
        this->getStudent()->getCart()->clearCart();
        cartDetailsWindow->updateView();
        cartDetailsWindow->setMessage("Your order has been submitted.");
    } else {
        cartDetailsWindow->setError("Error: Unable to submit your order. Please try again later.");
    }


}


#ifndef PLACEORDERCONTROL_H
#define PLACEORDERCONTROL_H

#include "CartRequestsAPI.h"
#include "Entity/Student.h"
#include "Entity/Order.h"
#include "Entity/SellableItem.h"
#include "BillingWindow.h"


#include <QObject>
#include <CartDetailsWindow.h>
#include <QUuid>

class BillingWindow;
class CartDetailsWindow;

class PlaceOrderControl : public QObject
{
    Q_OBJECT

    public:
        PlaceOrderControl(CartDetailsWindow *, CartRequestsAPI *);
        ~PlaceOrderControl();

        void submitOrder();
        void launchBillingWindow();
        CartRequestsAPI* getRequestAPI();

        Student* getStudent(); // Get the student from the requestAPI

    private slots:
        void orderStatusReceived(QUuid, int);

    private:
        CartDetailsWindow *cartDetailsWindow;
        CartRequestsAPI *requestAPI;
        BillingWindow *billingWindow;

};

#endif // PLACEORDERCONTROL_H

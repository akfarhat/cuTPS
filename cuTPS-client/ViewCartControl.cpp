#include "ViewCartControl.h"

#include "Entity/CreditcardInfo.h"

ViewCartControl::ViewCartControl(QWidget *parent, CartRequestsAPI *api) : parentWidget(parent), requestAPI(api) {


}

ViewCartControl::~ViewCartControl() {
    delete detailsWindow;
}



void ViewCartControl::launchCartDetailsWindow() {

    detailsWindow = new CartDetailsWindow(parentWidget, requestAPI);

    detailsWindow->exec();

}


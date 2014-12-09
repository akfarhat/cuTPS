#include "ViewCartControl.h"


ViewCartControl::ViewCartControl(CartRequestsAPI *api) : requestAPI(api)
{

}

ViewCartControl::~ViewCartControl()
{
    requestAPI = NULL;

    if (detailsWindow != NULL)
        delete detailsWindow;
}

void ViewCartControl::launchCartDetailsWindow()
{

    detailsWindow = new CartDetailsWindow(0, requestAPI);

    QObject::connect(detailsWindow, SIGNAL(cartDetailsWindowClosed()), this, SLOT(cartDetailsWindowClosed()));

    detailsWindow->exec();

}


void ViewCartControl::cartDetailsWindowClosed()
{

    detailsWindow = NULL;
    requestAPI = NULL;

    emit viewCartControlFinished();
}


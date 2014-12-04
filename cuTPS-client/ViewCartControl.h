#ifndef VIEWCARTCONTROL_H
#define VIEWCARTCONTROL_H

#include "Entity/Student.h"
#include "ClientNetworkHandler.h"
#include "CartRequestsAPI.h"
#include "CartDetailsWindow.h"

class ViewCartControl {
    public:
        ViewCartControl(ClientNetworkHandler *);
        ~ViewCartControl();

        void launchCartDetailsWindow();

    private:
        User *student;
        ClientNetworkHandler *network;
        CartRequestsAPI *requestAPI;

        CartDetailsWindow *detailsWindow;
};

#endif // VIEWCARTCONTROL_H

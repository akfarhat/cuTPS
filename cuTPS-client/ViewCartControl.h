#ifndef VIEWCARTCONTROL_H
#define VIEWCARTCONTROL_H

#include "Entity/Student.h"
#include "ClientNetworkHandler.h"
#include "CartRequestsAPI.h"
#include "CartDetailsWindow.h"
#include "Entity/Student.h"

class CartDetailsWindow;

class ViewCartControl {
    public:
        ViewCartControl(ClientNetworkHandler *, Student *);
        ~ViewCartControl();

        void launchCartDetailsWindow();

        Student* getStudent();

    private:
        Student *student;
        ClientNetworkHandler *network;
        CartRequestsAPI *requestAPI;

        CartDetailsWindow *detailsWindow;
};

#endif // VIEWCARTCONTROL_H

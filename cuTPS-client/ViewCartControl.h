#ifndef VIEWCARTCONTROL_H
#define VIEWCARTCONTROL_H

#include "Entity/Student.h"
#include "ClientNetworkHandler.h"
#include "CartRequestsAPI.h"
#include "CartDetailsWindow.h"
#include "Entity/Student.h"

#include <QWidget>

class CartDetailsWindow;

class ViewCartControl {
    public:
        ViewCartControl(QWidget *parent, ClientNetworkHandler *, Student *);
        ~ViewCartControl();

        void launchCartDetailsWindow();

        Student* getStudent();

    private:
        QWidget *parentWidget;
        Student *student;
        ClientNetworkHandler *network;
        CartRequestsAPI *requestAPI;

        CartDetailsWindow *detailsWindow;
};

#endif // VIEWCARTCONTROL_H

#ifndef VIEWCARTCONTROL_H
#define VIEWCARTCONTROL_H

#include "ClientNetworkHandler.h"
#include "CartRequestsAPI.h"
#include "CartDetailsWindow.h"

#include <QWidget>
#include <QObject>

class CartDetailsWindow;

class ViewCartControl: public QObject {
    Q_OBJECT

    public:
        ViewCartControl(CartRequestsAPI *);
        ~ViewCartControl();

        void launchCartDetailsWindow();

    signals:
        void viewCartControlFinished();

    private slots:
        void cartDetailsWindowClosed();


    private:
        CartRequestsAPI *requestAPI;
        CartDetailsWindow *detailsWindow;
};

#endif // VIEWCARTCONTROL_H

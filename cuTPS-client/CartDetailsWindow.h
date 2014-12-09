// Class: CartDetailsWindow
// Type: Boundary
// Description:
//     this class is responsible for displaying a student's shopping cart details
//
// Traceability: CartDetailsWindow class in the CartManagement subsystem
// Class: CartDetailsWindow
// Type: Boundary
// Description:
//     this class is responsible for displaying all items and their prices currently in a student's shopping cart.
//     It also provides options for placing or cancelling an order
//
// Traceability: CartDetailsWindow class in the CartManagement subsystem

#ifndef CARTDETAILSWINDOW_H
#define CARTDETAILSWINDOW_H

#include <QDialog>

#include "CartRequestsAPI.h"
#include "CancelOrderControl.h"
#include "PlaceOrderControl.h"


namespace Ui {
    class CartDetailsWindow;
}

class PlaceOrderControl;

class CartDetailsWindow : public QDialog {
    Q_OBJECT

    friend class PlaceOrderControl;

    public:
         explicit CartDetailsWindow(QWidget *parent = 0, CartRequestsAPI *api = NULL);
        ~CartDetailsWindow();

    signals:
        void cartDetailsWindowClosed();

    private slots:
        void on_backButton_clicked();
        void on_cancelOrderButton_clicked();
        void on_placeOrderButton_clicked();

        void placeOrderControlFinished();

    private:
        Ui::CartDetailsWindow *ui;
        CartRequestsAPI *requestAPI;

        PlaceOrderControl *placeOrderCtrl;

        void updateView();
        void setError(QString);
        void setMessage(QString);

};

#endif // CARTDETAILSWINDOW_H

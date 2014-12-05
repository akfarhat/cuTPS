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

#include <QMainWindow>

#include "CartRequestsAPI.h"
#include "ViewCartControl.h"
#include "CancelOrderControl.h"

// Forward reference to avoid circular deps
class ViewCartControl;

namespace Ui {
    class CartDetailsWindow;
}

class CartDetailsWindow : public QMainWindow {
    Q_OBJECT

    public:
         explicit CartDetailsWindow(QWidget *parent = 0, ViewCartControl *ctrl = NULL, CartRequestsAPI *api = NULL);
        ~CartDetailsWindow();

    signals:
        void cartNavigateBack();

    private slots:
        void on_backButton_clicked();
        void on_cancelOrderButton_clicked();
        void on_placeOrderButton_clicked();


    private:
        Ui::CartDetailsWindow *ui;
        ViewCartControl *viewCartCtrl;
        CartRequestsAPI *requestAPI;

};

#endif // CARTDETAILSWINDOW_H

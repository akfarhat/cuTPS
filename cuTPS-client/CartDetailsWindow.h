// Class: CartDetailsWindow
// Type: Boundary
// Description:
//     this class is responsible for displaying a student's shopping cart details
//
// Traceability: CartDetailsWindow class in the CartManagement subsystem

#ifndef CARTDETAILSWINDOW_H
#define CARTDETAILSWINDOW_H

#include <QMainWindow>

#include "CartRequestsAPI.h"

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
